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
struct smack_known {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_OVERRIDE ; 
 int EACCES ; 
 scalar_t__ smack_privileged (int /*<<< orphan*/ ) ; 
 struct smack_known* smack_syslog_label ; 
 struct smack_known* smk_of_current () ; 

__attribute__((used)) static int smack_syslog(int typefrom_file)
{
	int rc = 0;
	struct smack_known *skp = smk_of_current();

	if (smack_privileged(CAP_MAC_OVERRIDE))
		return 0;

	if (smack_syslog_label != NULL && smack_syslog_label != skp)
		rc = -EACCES;

	return rc;
}