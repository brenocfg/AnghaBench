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
struct rtcanmsg {int flags; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_MAX_DLEN ; 
 int /*<<< orphan*/  CAN_MAX_DLEN ; 
 int CGW_FLAGS_CAN_FD ; 
 int EINVAL ; 

__attribute__((used)) static int cgw_chk_csum_parms(s8 fr, s8 to, s8 re, struct rtcanmsg *r)
{
	s8 dlen = CAN_MAX_DLEN;

	if (r->flags & CGW_FLAGS_CAN_FD)
		dlen = CANFD_MAX_DLEN;

	/* absolute dlc values 0 .. 7 => 0 .. 7, e.g. data [0]
	 * relative to received dlc -1 .. -8 :
	 * e.g. for received dlc = 8
	 * -1 => index = 7 (data[7])
	 * -3 => index = 5 (data[5])
	 * -8 => index = 0 (data[0])
	 */

	if (fr >= -dlen && fr < dlen &&
	    to >= -dlen && to < dlen &&
	    re >= -dlen && re < dlen)
		return 0;
	else
		return -EINVAL;
}