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
typedef  size_t u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 size_t MGMT_STATUS_FAILED ; 
 size_t* mgmt_status_table ; 

__attribute__((used)) static u8 mgmt_status(u8 hci_status)
{
	if (hci_status < ARRAY_SIZE(mgmt_status_table))
		return mgmt_status_table[hci_status];

	return MGMT_STATUS_FAILED;
}