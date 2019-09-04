#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spi_master {int bus_num; int num_chipselect; } ;
struct parport {int /*<<< orphan*/  name; TYPE_1__* physport; } ;
struct pardevice {int dummy; } ;
struct pardev_cb {struct butterfly* private; } ;
struct device {int dummy; } ;
struct TYPE_8__ {struct spi_master* master; int /*<<< orphan*/ * txrx_word; int /*<<< orphan*/  chipselect; } ;
struct butterfly {TYPE_4__ bitbang; struct pardevice* pd; struct parport* port; TYPE_2__* dataflash; TYPE_3__* info; int /*<<< orphan*/  lastbyte; } ;
typedef  int /*<<< orphan*/  butterfly_cb ;
struct TYPE_7__ {int max_speed_hz; int chip_select; struct butterfly* controller_data; int /*<<< orphan*/ * platform_data; int /*<<< orphan*/  modalias; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t SPI_MODE_0 ; 
 struct butterfly* butterfly ; 
 int /*<<< orphan*/  butterfly_chipselect ; 
 int /*<<< orphan*/  butterfly_nreset ; 
 int /*<<< orphan*/  butterfly_txrx_word_mode0 ; 
 int dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flash ; 
 int /*<<< orphan*/  memset (struct pardev_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int parport_claim (struct pardevice*) ; 
 int /*<<< orphan*/  parport_frob_control (struct parport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pardevice* parport_register_dev_model (struct parport*,char*,struct pardev_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_release (struct pardevice*) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct spi_master* spi_alloc_master (struct device*,int) ; 
 int spi_bitbang_start (TYPE_4__*) ; 
 int /*<<< orphan*/  spi_cs_bit ; 
 struct butterfly* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 TYPE_2__* spi_new_device (struct spi_master*,TYPE_3__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vcc_bits ; 

__attribute__((used)) static void butterfly_attach(struct parport *p)
{
	struct pardevice	*pd;
	int			status;
	struct butterfly	*pp;
	struct spi_master	*master;
	struct device		*dev = p->physport->dev;
	struct pardev_cb	butterfly_cb;

	if (butterfly || !dev)
		return;

	/* REVISIT:  this just _assumes_ a butterfly is there ... no probe,
	 * and no way to be selective about what it binds to.
	 */

	master = spi_alloc_master(dev, sizeof(*pp));
	if (!master) {
		status = -ENOMEM;
		goto done;
	}
	pp = spi_master_get_devdata(master);

	/*
	 * SPI and bitbang hookup
	 *
	 * use default setup(), cleanup(), and transfer() methods; and
	 * only bother implementing mode 0.  Start it later.
	 */
	master->bus_num = 42;
	master->num_chipselect = 2;

	pp->bitbang.master = master;
	pp->bitbang.chipselect = butterfly_chipselect;
	pp->bitbang.txrx_word[SPI_MODE_0] = butterfly_txrx_word_mode0;

	/*
	 * parport hookup
	 */
	pp->port = p;
	memset(&butterfly_cb, 0, sizeof(butterfly_cb));
	butterfly_cb.private = pp;
	pd = parport_register_dev_model(p, "spi_butterfly", &butterfly_cb, 0);
	if (!pd) {
		status = -ENOMEM;
		goto clean0;
	}
	pp->pd = pd;

	status = parport_claim(pd);
	if (status < 0)
		goto clean1;

	/*
	 * Butterfly reset, powerup, run firmware
	 */
	pr_debug("%s: powerup/reset Butterfly\n", p->name);

	/* nCS for dataflash (this bit is inverted on output) */
	parport_frob_control(pp->port, spi_cs_bit, 0);

	/* stabilize power with chip in reset (nRESET), and
	 * spi_sck_bit clear (CPOL=0)
	 */
	pp->lastbyte |= vcc_bits;
	parport_write_data(pp->port, pp->lastbyte);
	msleep(5);

	/* take it out of reset; assume long reset delay */
	pp->lastbyte |= butterfly_nreset;
	parport_write_data(pp->port, pp->lastbyte);
	msleep(100);

	/*
	 * Start SPI ... for now, hide that we're two physical busses.
	 */
	status = spi_bitbang_start(&pp->bitbang);
	if (status < 0)
		goto clean2;

	/* Bus 1 lets us talk to at45db041b (firmware disables AVR SPI), AVR
	 * (firmware resets at45, acts as spi slave) or neither (we ignore
	 * both, AVR uses AT45).  Here we expect firmware for the first option.
	 */

	pp->info[0].max_speed_hz = 15 * 1000 * 1000;
	strcpy(pp->info[0].modalias, "mtd_dataflash");
	pp->info[0].platform_data = &flash;
	pp->info[0].chip_select = 1;
	pp->info[0].controller_data = pp;
	pp->dataflash = spi_new_device(pp->bitbang.master, &pp->info[0]);
	if (pp->dataflash)
		pr_debug("%s: dataflash at %s\n", p->name,
			 dev_name(&pp->dataflash->dev));

	pr_info("%s: AVR Butterfly\n", p->name);
	butterfly = pp;
	return;

clean2:
	/* turn off VCC */
	parport_write_data(pp->port, 0);

	parport_release(pp->pd);
clean1:
	parport_unregister_device(pd);
clean0:
	spi_master_put(pp->bitbang.master);
done:
	pr_debug("%s: butterfly probe, fail %d\n", p->name, status);
}