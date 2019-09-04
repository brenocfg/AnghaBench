#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pool; } ;
struct TYPE_4__ {scalar_t__ pool; TYPE_1__ state; } ;
typedef  TYPE_2__ ngx_http_v2_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_destroy_pool (scalar_t__) ; 

__attribute__((used)) static void
ngx_http_v2_pool_cleanup(void *data)
{
    ngx_http_v2_connection_t  *h2c = data;

    if (h2c->state.pool) {
        ngx_destroy_pool(h2c->state.pool);
    }

    if (h2c->pool) {
        ngx_destroy_pool(h2c->pool);
    }
}