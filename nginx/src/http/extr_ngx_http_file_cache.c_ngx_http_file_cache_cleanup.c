#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; TYPE_1__ file; int /*<<< orphan*/  background; scalar_t__ updating; scalar_t__ updated; } ;
typedef  TYPE_2__ ngx_http_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_file_cache_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_file_cache_cleanup(void *data)
{
    ngx_http_cache_t  *c = data;

    if (c->updated) {
        return;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->file.log, 0,
                   "http file cache cleanup");

    if (c->updating && !c->background) {
        ngx_log_error(NGX_LOG_ALERT, c->file.log, 0,
                      "stalled cache updating, error:%ui", c->error);
    }

    ngx_http_file_cache_free(c, NULL);
}