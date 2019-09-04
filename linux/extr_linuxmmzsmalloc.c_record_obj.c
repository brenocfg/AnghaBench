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
 int /*<<< orphan*/  WRITE_ONCE (unsigned long,unsigned long) ; 

__attribute__((used)) static void record_obj(unsigned long handle, unsigned long obj)
{
	/*
	 * lsb of @obj represents handle lock while other bits
	 * represent object value the handle is pointing so
	 * updating shouldn't do store tearing.
	 */
	WRITE_ONCE(*(unsigned long *)handle, obj);
}