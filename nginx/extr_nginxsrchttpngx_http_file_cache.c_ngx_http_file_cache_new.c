#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_9__ {TYPE_1__* connection; TYPE_4__* cache; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_8__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  log; } ;
struct TYPE_10__ {TYPE_2__ file; int /*<<< orphan*/  keys; } ;
typedef  TYPE_4__ ngx_http_cache_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_INVALID_FILE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_int_t
ngx_http_file_cache_new(ngx_http_request_t *r)
{
    ngx_http_cache_t  *c;

    c = ngx_pcalloc(r->pool, sizeof(ngx_http_cache_t));
    if (c == NULL) {
        return NGX_ERROR;
    }

    if (ngx_array_init(&c->keys, r->pool, 4, sizeof(ngx_str_t)) != NGX_OK) {
        return NGX_ERROR;
    }

    r->cache = c;
    c->file.log = r->connection->log;
    c->file.fd = NGX_INVALID_FILE;

    return NGX_OK;
}