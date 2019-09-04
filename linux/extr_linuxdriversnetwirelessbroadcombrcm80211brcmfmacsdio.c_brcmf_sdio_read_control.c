#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long uint ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  rxc_errors; int /*<<< orphan*/  f2rxdata; int /*<<< orphan*/  rx_toolong; } ;
struct brcmf_sdio {unsigned long head_align; long roundup; long blocksize; long rxlen; int /*<<< orphan*/  rxctl_lock; int /*<<< orphan*/ * rxctl_orig; int /*<<< orphan*/ * rxctl; TYPE_2__ sdcnt; TYPE_3__* sdiodev; int /*<<< orphan*/ * rxbuf; scalar_t__ rxblen; } ;
struct TYPE_6__ {TYPE_1__* bus_if; } ;
struct TYPE_4__ {long maxctl; } ;

/* Variables and functions */
 scalar_t__ BRCMF_BYTES_ON () ; 
 scalar_t__ BRCMF_CTL_ON () ; 
 long BRCMF_FIRSTREAD ; 
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_dbg_hex_dump (int,int /*<<< orphan*/ *,long,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int /*<<< orphan*/  brcmf_sdio_dcmd_resp_wake (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdio_rxfail (struct brcmf_sdio*,int,int) ; 
 int brcmf_sdiod_recv_buf (TYPE_3__*,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (scalar_t__) ; 

__attribute__((used)) static void
brcmf_sdio_read_control(struct brcmf_sdio *bus, u8 *hdr, uint len, uint doff)
{
	uint rdlen, pad;
	u8 *buf = NULL, *rbuf;
	int sdret;

	brcmf_dbg(SDIO, "Enter\n");
	if (bus->rxblen)
		buf = vzalloc(bus->rxblen);
	if (!buf)
		goto done;

	rbuf = bus->rxbuf;
	pad = ((unsigned long)rbuf % bus->head_align);
	if (pad)
		rbuf += (bus->head_align - pad);

	/* Copy the already-read portion over */
	memcpy(buf, hdr, BRCMF_FIRSTREAD);
	if (len <= BRCMF_FIRSTREAD)
		goto gotpkt;

	/* Raise rdlen to next SDIO block to avoid tail command */
	rdlen = len - BRCMF_FIRSTREAD;
	if (bus->roundup && bus->blocksize && (rdlen > bus->blocksize)) {
		pad = bus->blocksize - (rdlen % bus->blocksize);
		if ((pad <= bus->roundup) && (pad < bus->blocksize) &&
		    ((len + pad) < bus->sdiodev->bus_if->maxctl))
			rdlen += pad;
	} else if (rdlen % bus->head_align) {
		rdlen += bus->head_align - (rdlen % bus->head_align);
	}

	/* Drop if the read is too big or it exceeds our maximum */
	if ((rdlen + BRCMF_FIRSTREAD) > bus->sdiodev->bus_if->maxctl) {
		brcmf_err("%d-byte control read exceeds %d-byte buffer\n",
			  rdlen, bus->sdiodev->bus_if->maxctl);
		brcmf_sdio_rxfail(bus, false, false);
		goto done;
	}

	if ((len - doff) > bus->sdiodev->bus_if->maxctl) {
		brcmf_err("%d-byte ctl frame (%d-byte ctl data) exceeds %d-byte limit\n",
			  len, len - doff, bus->sdiodev->bus_if->maxctl);
		bus->sdcnt.rx_toolong++;
		brcmf_sdio_rxfail(bus, false, false);
		goto done;
	}

	/* Read remain of frame body */
	sdret = brcmf_sdiod_recv_buf(bus->sdiodev, rbuf, rdlen);
	bus->sdcnt.f2rxdata++;

	/* Control frame failures need retransmission */
	if (sdret < 0) {
		brcmf_err("read %d control bytes failed: %d\n",
			  rdlen, sdret);
		bus->sdcnt.rxc_errors++;
		brcmf_sdio_rxfail(bus, true, true);
		goto done;
	} else
		memcpy(buf + BRCMF_FIRSTREAD, rbuf, rdlen);

gotpkt:

	brcmf_dbg_hex_dump(BRCMF_BYTES_ON() && BRCMF_CTL_ON(),
			   buf, len, "RxCtrl:\n");

	/* Point to valid data and indicate its length */
	spin_lock_bh(&bus->rxctl_lock);
	if (bus->rxctl) {
		brcmf_err("last control frame is being processed.\n");
		spin_unlock_bh(&bus->rxctl_lock);
		vfree(buf);
		goto done;
	}
	bus->rxctl = buf + doff;
	bus->rxctl_orig = buf;
	bus->rxlen = len - doff;
	spin_unlock_bh(&bus->rxctl_lock);

done:
	/* Awake any waiters */
	brcmf_sdio_dcmd_resp_wake(bus);
}