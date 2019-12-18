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
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* DUMMY_PTR ; 

int idr_u32_cb(int id, void *ptr, void *data)
{
	BUG_ON(id < 0);
	BUG_ON(ptr != DUMMY_PTR);
	return 0;
}