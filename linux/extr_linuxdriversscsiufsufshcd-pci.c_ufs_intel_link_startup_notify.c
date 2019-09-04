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
struct ufs_hba {int dummy; } ;
typedef  enum ufs_notify_change_status { ____Placeholder_ufs_notify_change_status } ufs_notify_change_status ;

/* Variables and functions */
#define  POST_CHANGE 129 
#define  PRE_CHANGE 128 
 int ufs_intel_disable_lcc (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_intel_link_startup_notify(struct ufs_hba *hba,
					 enum ufs_notify_change_status status)
{
	int err = 0;

	switch (status) {
	case PRE_CHANGE:
		err = ufs_intel_disable_lcc(hba);
		break;
	case POST_CHANGE:
		break;
	default:
		break;
	}

	return err;
}