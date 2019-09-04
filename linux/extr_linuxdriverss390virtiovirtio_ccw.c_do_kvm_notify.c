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
struct subchannel_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG_STAT_X500 ; 
 long __do_kvm_notify (struct subchannel_id,unsigned long,long) ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline long do_kvm_notify(struct subchannel_id schid,
				 unsigned long queue_index,
				 long cookie)
{
	diag_stat_inc(DIAG_STAT_X500);
	return __do_kvm_notify(schid, queue_index, cookie);
}