#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int len; int valid; int /*<<< orphan*/ * data; scalar_t__ not_found; scalar_t__ no_cacheable; } ;
typedef  TYPE_2__ ngx_stream_variable_value_t ;
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_stream_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ SOCK_DGRAM ; 

__attribute__((used)) static ngx_int_t
ngx_stream_variable_protocol(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->len = 3;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = (u_char *) (s->connection->type == SOCK_DGRAM ? "UDP" : "TCP");

    return NGX_OK;
}