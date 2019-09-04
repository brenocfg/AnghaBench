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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ L2CAP_PSM_LE_DYN_END ; 
 scalar_t__ L2CAP_PSM_LE_DYN_START ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2cap_validate_le_psm(u16 psm)
{
	/* Valid LE_PSM ranges are defined only until 0x00ff */
	if (psm > L2CAP_PSM_LE_DYN_END)
		return -EINVAL;

	/* Restrict fixed, SIG assigned PSM values to CAP_NET_BIND_SERVICE */
	if (psm < L2CAP_PSM_LE_DYN_START && !capable(CAP_NET_BIND_SERVICE))
		return -EACCES;

	return 0;
}