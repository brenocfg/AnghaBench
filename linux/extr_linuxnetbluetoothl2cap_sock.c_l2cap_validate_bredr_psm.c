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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int EACCES ; 
 int EINVAL ; 
 int L2CAP_PSM_DYN_START ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2cap_validate_bredr_psm(u16 psm)
{
	/* PSM must be odd and lsb of upper byte must be 0 */
	if ((psm & 0x0101) != 0x0001)
		return -EINVAL;

	/* Restrict usage of well-known PSMs */
	if (psm < L2CAP_PSM_DYN_START && !capable(CAP_NET_BIND_SERVICE))
		return -EACCES;

	return 0;
}