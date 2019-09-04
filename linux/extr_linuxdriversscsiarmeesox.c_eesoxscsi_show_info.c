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
struct seq_file {int dummy; } ;
struct eesoxscsi_info {int control; int /*<<< orphan*/  info; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int EESOX_TERM_ENABLE ; 
 char* VERSION ; 
 int /*<<< orphan*/  fas216_print_devices (int /*<<< orphan*/ *,struct seq_file*) ; 
 int /*<<< orphan*/  fas216_print_host (int /*<<< orphan*/ *,struct seq_file*) ; 
 int /*<<< orphan*/  fas216_print_stats (int /*<<< orphan*/ *,struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int eesoxscsi_show_info(struct seq_file *m, struct Scsi_Host *host)
{
	struct eesoxscsi_info *info;

	info = (struct eesoxscsi_info *)host->hostdata;

	seq_printf(m, "EESOX SCSI driver v%s\n", VERSION);
	fas216_print_host(&info->info, m);
	seq_printf(m, "Term    : o%s\n",
			info->control & EESOX_TERM_ENABLE ? "n" : "ff");

	fas216_print_stats(&info->info, m);
	fas216_print_devices(&info->info, m);
	return 0;
}