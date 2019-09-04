#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  stats; int /*<<< orphan*/  tsf; int /*<<< orphan*/  ready; } ;
struct wil6210_priv {TYPE_1__ fw_stats_global; } ;
struct seq_file {struct wil6210_priv* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_link_stats_print_global (struct wil6210_priv*,struct seq_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wil_link_stats_global_debugfs_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;

	if (!wil->fw_stats_global.ready)
		return 0;

	seq_printf(s, "TSF %lld\n", wil->fw_stats_global.tsf);
	wil_link_stats_print_global(wil, s, &wil->fw_stats_global.stats);

	return 0;
}