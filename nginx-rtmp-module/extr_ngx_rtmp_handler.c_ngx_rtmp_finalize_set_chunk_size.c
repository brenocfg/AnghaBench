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
struct TYPE_3__ {scalar_t__ in_chunk_size_changing; int /*<<< orphan*/ * in_old_pool; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_finalize_set_chunk_size(ngx_rtmp_session_t *s)
{
    if (s->in_chunk_size_changing && s->in_old_pool) {
        ngx_destroy_pool(s->in_old_pool);
        s->in_old_pool = NULL;
        s->in_chunk_size_changing = 0;
    }
    return NGX_OK;
}