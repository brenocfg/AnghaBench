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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {int host_no; TYPE_1__ shost_gendev; } ;
typedef  int /*<<< orphan*/  event_string ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
#define  QEDF_UEVENT_CODE_GRCDUMP 128 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strscpy (char*,char*,int) ; 

void
qedf_uevent_emit(struct Scsi_Host *shost, u32 code, char *msg)
{
	char event_string[40];
	char *envp[] = {event_string, NULL};

	memset(event_string, 0, sizeof(event_string));
	switch (code) {
	case QEDF_UEVENT_CODE_GRCDUMP:
		if (msg)
			strscpy(event_string, msg, sizeof(event_string));
		else
			sprintf(event_string, "GRCDUMP=%u", shost->host_no);
		break;
	default:
		/* do nothing */
		break;
	}

	kobject_uevent_env(&shost->shost_gendev.kobj, KOBJ_CHANGE, envp);
}