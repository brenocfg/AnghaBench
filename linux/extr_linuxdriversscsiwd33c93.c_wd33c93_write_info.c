#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Scsi_Host {int dummy; } ;

/* Variables and functions */

int wd33c93_write_info(struct Scsi_Host *instance, char *buf, int len)
{
#ifdef PROC_INTERFACE
	char *bp;
	struct WD33C93_hostdata *hd;
	int x;

	hd = (struct WD33C93_hostdata *) instance->hostdata;

/* We accept the following
 * keywords (same format as command-line, but arguments are not optional):
 *    debug
 *    disconnect
 *    period
 *    resync
 *    proc
 *    nodma
 *    level2
 *    burst
 *    fast
 *    nosync
 */

	buf[len] = '\0';
	for (bp = buf; *bp; ) {
		while (',' == *bp || ' ' == *bp)
			++bp;
	if (!strncmp(bp, "debug:", 6)) {
			hd->args = simple_strtoul(bp+6, &bp, 0) & DB_MASK;
	} else if (!strncmp(bp, "disconnect:", 11)) {
			x = simple_strtoul(bp+11, &bp, 0);
		if (x < DIS_NEVER || x > DIS_ALWAYS)
			x = DIS_ADAPTIVE;
		hd->disconnect = x;
	} else if (!strncmp(bp, "period:", 7)) {
		x = simple_strtoul(bp+7, &bp, 0);
		hd->default_sx_per =
			hd->sx_table[round_period((unsigned int) x,
						  hd->sx_table)].period_ns;
	} else if (!strncmp(bp, "resync:", 7)) {
			set_resync(hd, (int)simple_strtoul(bp+7, &bp, 0));
	} else if (!strncmp(bp, "proc:", 5)) {
			hd->proc = simple_strtoul(bp+5, &bp, 0);
	} else if (!strncmp(bp, "nodma:", 6)) {
			hd->no_dma = simple_strtoul(bp+6, &bp, 0);
	} else if (!strncmp(bp, "level2:", 7)) {
			hd->level2 = simple_strtoul(bp+7, &bp, 0);
		} else if (!strncmp(bp, "burst:", 6)) {
			hd->dma_mode =
				simple_strtol(bp+6, &bp, 0) ? CTRL_BURST:CTRL_DMA;
		} else if (!strncmp(bp, "fast:", 5)) {
			x = !!simple_strtol(bp+5, &bp, 0);
			if (x != hd->fast)
				set_resync(hd, 0xff);
			hd->fast = x;
		} else if (!strncmp(bp, "nosync:", 7)) {
			x = simple_strtoul(bp+7, &bp, 0);
			set_resync(hd, x ^ hd->no_sync);
			hd->no_sync = x;
		} else {
			break; /* unknown keyword,syntax-error,... */
		}
	}
	return len;
#else
	return 0;
#endif
}