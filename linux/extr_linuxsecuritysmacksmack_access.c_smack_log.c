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
struct smk_audit_info {int dummy; } ;

/* Variables and functions */

void smack_log(char *subject_label, char *object_label, int request,
               int result, struct smk_audit_info *ad)
{
}