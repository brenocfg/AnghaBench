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
struct rrdengine_instance {int dummy; } ;
struct rrdeng_page_descr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pg_cache_put (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 

void rrdeng_put_page(struct rrdengine_instance *ctx, void *handle)
{
    (void)ctx;
    pg_cache_put(ctx, (struct rrdeng_page_descr *)handle);
}