#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct bcm_msg_head {TYPE_1__ ival2; TYPE_2__ ival1; } ;

/* Variables and functions */
 scalar_t__ BCM_TIMER_SEC_MAX ; 
 scalar_t__ USEC_PER_SEC ; 

__attribute__((used)) static bool bcm_is_invalid_tv(struct bcm_msg_head *msg_head)
{
	if ((msg_head->ival1.tv_sec < 0) ||
	    (msg_head->ival1.tv_sec > BCM_TIMER_SEC_MAX) ||
	    (msg_head->ival1.tv_usec < 0) ||
	    (msg_head->ival1.tv_usec >= USEC_PER_SEC) ||
	    (msg_head->ival2.tv_sec < 0) ||
	    (msg_head->ival2.tv_sec > BCM_TIMER_SEC_MAX) ||
	    (msg_head->ival2.tv_usec < 0) ||
	    (msg_head->ival2.tv_usec >= USEC_PER_SEC))
		return true;

	return false;
}