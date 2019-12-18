#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  allocations; } ;
typedef  TYPE_1__ ser_context ;

/* Variables and functions */
 void* emalloc (size_t) ; 
 int /*<<< orphan*/  zend_llist_add_element (int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static inline void *accounted_emalloc(size_t alloc_size, ser_context *ctx)
{
	void *ret = emalloc(alloc_size);
	zend_llist_add_element(&ctx->allocations, &ret);
	return ret;
}