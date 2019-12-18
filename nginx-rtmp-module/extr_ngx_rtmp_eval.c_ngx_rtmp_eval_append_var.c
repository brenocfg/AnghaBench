#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* handler ) (void*,TYPE_3__*,TYPE_2__*) ;TYPE_1__ name; } ;
typedef  TYPE_3__ ngx_rtmp_eval_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_eval_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void
ngx_rtmp_eval_append_var(void *ctx, ngx_buf_t *b, ngx_rtmp_eval_t **e,
    ngx_str_t *name, ngx_log_t *log)
{
    ngx_uint_t          k;
    ngx_str_t           v;
    ngx_rtmp_eval_t    *ee;

    for (; *e; ++e) {
        for (k = 0, ee = *e; ee->handler; ++k, ++ee) {
            if (ee->name.len == name->len &&
                ngx_memcmp(ee->name.data, name->data, name->len) == 0)
            {
                ee->handler(ctx, ee, &v);
                ngx_rtmp_eval_append(b, v.data, v.len, log);
            }
        }
    }
}