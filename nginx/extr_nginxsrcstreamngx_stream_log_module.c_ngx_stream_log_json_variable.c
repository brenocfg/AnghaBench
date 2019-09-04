#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {scalar_t__ escape; int /*<<< orphan*/  len; int /*<<< orphan*/  data; scalar_t__ not_found; } ;
typedef  TYPE_1__ ngx_stream_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_stream_session_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_stream_log_op_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_escape_json (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_stream_get_indexed_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char *
ngx_stream_log_json_variable(ngx_stream_session_t *s, u_char *buf,
    ngx_stream_log_op_t *op)
{
    ngx_stream_variable_value_t  *value;

    value = ngx_stream_get_indexed_variable(s, op->data);

    if (value == NULL || value->not_found) {
        return buf;
    }

    if (value->escape == 0) {
        return ngx_cpymem(buf, value->data, value->len);

    } else {
        return (u_char *) ngx_escape_json(buf, value->data, value->len);
    }
}