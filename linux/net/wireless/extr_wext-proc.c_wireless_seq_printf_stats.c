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
struct seq_file {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; scalar_t__ ieee80211_ptr; scalar_t__ wireless_handlers; } ;
struct TYPE_6__ {int updated; scalar_t__ noise; scalar_t__ level; int /*<<< orphan*/  qual; } ;
struct TYPE_5__ {int /*<<< orphan*/  beacon; } ;
struct TYPE_4__ {int /*<<< orphan*/  misc; int /*<<< orphan*/  retries; int /*<<< orphan*/  fragment; int /*<<< orphan*/  code; int /*<<< orphan*/  nwid; } ;
struct iw_statistics {TYPE_3__ qual; TYPE_2__ miss; TYPE_1__ discard; int /*<<< orphan*/  status; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int IW_QUAL_ALL_UPDATED ; 
 int IW_QUAL_DBM ; 
 int IW_QUAL_LEVEL_UPDATED ; 
 int IW_QUAL_NOISE_UPDATED ; 
 int IW_QUAL_QUAL_UPDATED ; 
 struct iw_statistics* get_wireless_stats (struct net_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,scalar_t__,char,scalar_t__,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wireless_seq_printf_stats(struct seq_file *seq,
				      struct net_device *dev)
{
	/* Get stats from the driver */
	struct iw_statistics *stats = get_wireless_stats(dev);
	static struct iw_statistics nullstats = {};

	/* show device if it's wireless regardless of current stats */
	if (!stats) {
#ifdef CONFIG_WIRELESS_EXT
		if (dev->wireless_handlers)
			stats = &nullstats;
#endif
#ifdef CONFIG_CFG80211
		if (dev->ieee80211_ptr)
			stats = &nullstats;
#endif
	}

	if (stats) {
		seq_printf(seq, "%6s: %04x  %3d%c  %3d%c  %3d%c  %6d %6d %6d "
				"%6d %6d   %6d\n",
			   dev->name, stats->status, stats->qual.qual,
			   stats->qual.updated & IW_QUAL_QUAL_UPDATED
			   ? '.' : ' ',
			   ((__s32) stats->qual.level) -
			   ((stats->qual.updated & IW_QUAL_DBM) ? 0x100 : 0),
			   stats->qual.updated & IW_QUAL_LEVEL_UPDATED
			   ? '.' : ' ',
			   ((__s32) stats->qual.noise) -
			   ((stats->qual.updated & IW_QUAL_DBM) ? 0x100 : 0),
			   stats->qual.updated & IW_QUAL_NOISE_UPDATED
			   ? '.' : ' ',
			   stats->discard.nwid, stats->discard.code,
			   stats->discard.fragment, stats->discard.retries,
			   stats->discard.misc, stats->miss.beacon);

		if (stats != &nullstats)
			stats->qual.updated &= ~IW_QUAL_ALL_UPDATED;
	}
}