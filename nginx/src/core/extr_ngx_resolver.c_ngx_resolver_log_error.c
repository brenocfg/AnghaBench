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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ ngx_resolver_connection_t ;
struct TYPE_5__ {TYPE_1__* data; int /*<<< orphan*/ * action; } ;
typedef  TYPE_2__ ngx_log_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,size_t,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_char *
ngx_resolver_log_error(ngx_log_t *log, u_char *buf, size_t len)
{
    u_char                     *p;
    ngx_resolver_connection_t  *rec;

    p = buf;

    if (log->action) {
        p = ngx_snprintf(buf, len, " while %s", log->action);
        len -= p - buf;
    }

    rec = log->data;

    if (rec) {
        p = ngx_snprintf(p, len, ", resolver: %V", &rec->server);
    }

    return p;
}