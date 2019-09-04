#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int state; int flags; int mflags; int usrate; int dsrate; int dsattenuation; int usattenuation; int dsmargin; int usmargin; } ;
struct TYPE_4__ {TYPE_1__ phy; } ;
struct uea_softc {TYPE_2__ stats; int /*<<< orphan*/  sync_q; int /*<<< orphan*/ * dsp_firm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_PHY_SIG_FOUND ; 
 int /*<<< orphan*/  E4_SA_DIAG ; 
 int /*<<< orphan*/  E4_SA_INFO ; 
 int /*<<< orphan*/  E4_SA_RATE ; 
 int /*<<< orphan*/  E4_SA_STAT ; 
 int EAGAIN ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_LOOPBACK_OFF ; 
 int /*<<< orphan*/  UEA_SET_MODE ; 
 int /*<<< orphan*/  UPDATE_ATM_SIGNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_ATM_STAT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link_rate ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_info (int /*<<< orphan*/ ,char*) ; 
 int uea_read_cmv_e4 (struct uea_softc*,int,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  uea_request (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_set_bulk_timeout (struct uea_softc*,int) ; 
 int /*<<< orphan*/  uea_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uea_stat_e4(struct uea_softc *sc)
{
	u32 data;
	u32 tmp_arr[2];
	int ret;

	uea_enters(INS_TO_USBDEV(sc));
	data = sc->stats.phy.state;

	/* XXX only need to be done before operationnal... */
	ret = uea_read_cmv_e4(sc, 1, E4_SA_STAT, 0, 0, &sc->stats.phy.state);
	if (ret < 0)
		return ret;

	switch (sc->stats.phy.state) {
	case 0x0:	/* not yet synchronized */
	case 0x1:
	case 0x3:
	case 0x4:
		uea_dbg(INS_TO_USBDEV(sc), "modem not yet "
						"synchronized\n");
		return 0;
	case 0x5:	/* initialization */
	case 0x6:
	case 0x9:
	case 0xa:
		uea_dbg(INS_TO_USBDEV(sc), "modem initializing\n");
		return 0;
	case 0x2:	/* fail ... */
		uea_info(INS_TO_USBDEV(sc), "modem synchronization "
				"failed (may be try other cmv/dsp)\n");
		return -EAGAIN;
	case 0x7:	/* operational */
		break;
	default:
		uea_warn(INS_TO_USBDEV(sc), "unknown state: %x\n",
						sc->stats.phy.state);
		return 0;
	}

	if (data != 7) {
		uea_request(sc, UEA_SET_MODE, UEA_LOOPBACK_OFF, 0, NULL);
		uea_info(INS_TO_USBDEV(sc), "modem operational\n");

		/* release the dsp firmware as it is not needed until
		 * the next failure
		 */
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = NULL;
	}

	/* always update it as atm layer could not be init when we switch to
	 * operational state
	 */
	UPDATE_ATM_SIGNAL(ATM_PHY_SIG_FOUND);

	/* wake up processes waiting for synchronization */
	wake_up(&sc->sync_q);

	/* TODO improve this state machine :
	 * we need some CMV info : what they do and their unit
	 * we should find the equivalent of eagle3- CMV
	 */
	/* check flags */
	ret = uea_read_cmv_e4(sc, 1, E4_SA_DIAG, 0, 0, &sc->stats.phy.flags);
	if (ret < 0)
		return ret;
	sc->stats.phy.mflags |= sc->stats.phy.flags;

	/* in case of a flags ( for example delineation LOSS (& 0x10)),
	 * we check the status again in order to detect the failure earlier
	 */
	if (sc->stats.phy.flags) {
		uea_dbg(INS_TO_USBDEV(sc), "Stat flag = 0x%x\n",
		       sc->stats.phy.flags);
		if (sc->stats.phy.flags & 1) /* delineation LOSS */
			return -EAGAIN;
		if (sc->stats.phy.flags & 0x4000) /* Reset Flag */
			return -EAGAIN;
		return 0;
	}

	/* rate data may be in upper or lower half of 64 bit word, strange */
	ret = uea_read_cmv_e4(sc, 4, E4_SA_RATE, 0, 0, tmp_arr);
	if (ret < 0)
		return ret;
	data = (tmp_arr[0]) ? tmp_arr[0] : tmp_arr[1];
	sc->stats.phy.usrate = data / 1000;

	ret = uea_read_cmv_e4(sc, 4, E4_SA_RATE, 1, 0, tmp_arr);
	if (ret < 0)
		return ret;
	data = (tmp_arr[0]) ? tmp_arr[0] : tmp_arr[1];
	uea_set_bulk_timeout(sc, data / 1000);
	sc->stats.phy.dsrate = data / 1000;
	UPDATE_ATM_STAT(link_rate, sc->stats.phy.dsrate * 1000 / 424);

	ret = uea_read_cmv_e4(sc, 1, E4_SA_INFO, 68, 1, &data);
	if (ret < 0)
		return ret;
	sc->stats.phy.dsattenuation = data / 10;

	ret = uea_read_cmv_e4(sc, 1, E4_SA_INFO, 69, 1, &data);
	if (ret < 0)
		return ret;
	sc->stats.phy.usattenuation = data / 10;

	ret = uea_read_cmv_e4(sc, 1, E4_SA_INFO, 68, 3, &data);
	if (ret < 0)
		return ret;
	sc->stats.phy.dsmargin = data / 2;

	ret = uea_read_cmv_e4(sc, 1, E4_SA_INFO, 69, 3, &data);
	if (ret < 0)
		return ret;
	sc->stats.phy.usmargin = data / 10;

	return 0;
}