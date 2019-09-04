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

/* Variables and functions */
 int /*<<< orphan*/  SECCLASS_SYSTEM ; 
 int /*<<< orphan*/  SECINITSID_KERNEL ; 
#define  SYSLOG_ACTION_CONSOLE_LEVEL 132 
#define  SYSLOG_ACTION_CONSOLE_OFF 131 
#define  SYSLOG_ACTION_CONSOLE_ON 130 
#define  SYSLOG_ACTION_READ_ALL 129 
#define  SYSLOG_ACTION_SIZE_BUFFER 128 
 int /*<<< orphan*/  SYSTEM__SYSLOG_CONSOLE ; 
 int /*<<< orphan*/  SYSTEM__SYSLOG_MOD ; 
 int /*<<< orphan*/  SYSTEM__SYSLOG_READ ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_syslog(int type)
{
	switch (type) {
	case SYSLOG_ACTION_READ_ALL:	/* Read last kernel messages */
	case SYSLOG_ACTION_SIZE_BUFFER:	/* Return size of the log buffer */
		return avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__SYSLOG_READ, NULL);
	case SYSLOG_ACTION_CONSOLE_OFF:	/* Disable logging to console */
	case SYSLOG_ACTION_CONSOLE_ON:	/* Enable logging to console */
	/* Set level of messages printed to console */
	case SYSLOG_ACTION_CONSOLE_LEVEL:
		return avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__SYSLOG_CONSOLE,
				    NULL);
	}
	/* All other syslog types */
	return avc_has_perm(&selinux_state,
			    current_sid(), SECINITSID_KERNEL,
			    SECCLASS_SYSTEM, SYSTEM__SYSLOG_MOD, NULL);
}