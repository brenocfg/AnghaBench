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
struct iwl_mvm {int max_scans; int* scan_uid_status; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int iwl_mvm_scan_uid_by_status(struct iwl_mvm *mvm, int status)
{
	int i;

	for (i = 0; i < mvm->max_scans; i++)
		if (mvm->scan_uid_status[i] == status)
			return i;

	return -ENOENT;
}