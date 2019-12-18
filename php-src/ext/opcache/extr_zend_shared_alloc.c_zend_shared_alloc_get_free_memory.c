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
 size_t ZSMMG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_free ; 

size_t zend_shared_alloc_get_free_memory(void)
{
	return ZSMMG(shared_free);
}