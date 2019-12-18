#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  l; } ;

/* Variables and functions */
 unsigned int CT_LOCKARRAY_MASK ; 
 TYPE_1__* __ip_vs_conntbl_lock_array ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ct_write_unlock_bh(unsigned int key)
{
	spin_unlock_bh(&__ip_vs_conntbl_lock_array[key&CT_LOCKARRAY_MASK].l);
}