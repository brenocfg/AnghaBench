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
 void* _zend_shared_memdup (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void *zend_shared_memdup_put_free(void *source, size_t size)
{
	return _zend_shared_memdup(source, size, 0, 0, 1, 1);
}