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

/* Variables and functions */
 scalar_t__ ZCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locked ; 
 int /*<<< orphan*/  zend_shared_alloc_unlock () ; 

void zend_shared_alloc_safe_unlock(void)
{
	if (ZCG(locked)) {
		zend_shared_alloc_unlock();
	}
}