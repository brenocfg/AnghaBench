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
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  refcount_add_not_zero_checked (unsigned int,int /*<<< orphan*/ *) ; 

void refcount_add_checked(unsigned int i, refcount_t *r)
{
	WARN_ONCE(!refcount_add_not_zero_checked(i, r), "refcount_t: addition on 0; use-after-free.\n");
}