#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* label; } ;
typedef  TYPE_1__ basebackup_options ;
typedef  int /*<<< orphan*/  activitymsg ;
struct TYPE_7__ {int /*<<< orphan*/  options; } ;
typedef  TYPE_2__ BaseBackupCmd ;

/* Variables and functions */
 int /*<<< orphan*/  WALSNDSTATE_BACKUP ; 
 int /*<<< orphan*/  WalSndSetState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_basebackup_options (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  perform_base_backup (TYPE_1__*) ; 
 int /*<<< orphan*/  set_ps_display (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ update_process_title ; 

void
SendBaseBackup(BaseBackupCmd *cmd)
{
	basebackup_options opt;

	parse_basebackup_options(cmd->options, &opt);

	WalSndSetState(WALSNDSTATE_BACKUP);

	if (update_process_title)
	{
		char		activitymsg[50];

		snprintf(activitymsg, sizeof(activitymsg), "sending backup \"%s\"",
				 opt.label);
		set_ps_display(activitymsg, false);
	}

	perform_base_backup(&opt);
}