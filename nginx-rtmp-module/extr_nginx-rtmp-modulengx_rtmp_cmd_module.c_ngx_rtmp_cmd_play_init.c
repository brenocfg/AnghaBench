#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
struct TYPE_12__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_13__ {scalar_t__ silent; scalar_t__ reset; scalar_t__ duration; scalar_t__ start; int /*<<< orphan*/  args; scalar_t__ name; } ;
typedef  TYPE_3__ ngx_rtmp_play_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_header_t ;
struct TYPE_14__ {int member_0; int member_3; scalar_t__* member_2; int /*<<< orphan*/  const member_1; } ;
typedef  TYPE_4__ ngx_rtmp_amf_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  in_elts ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
#define  NGX_RTMP_AMF_BOOLEAN 133 
#define  NGX_RTMP_AMF_NULL 132 
#define  NGX_RTMP_AMF_NUMBER 131 
#define  NGX_RTMP_AMF_OPTIONAL 130 
#define  NGX_RTMP_AMF_STRING 129 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__ const*,int) ; 
#define  ngx_null_string 128 
 int /*<<< orphan*/  ngx_rtmp_cmd_fill_args (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play (TYPE_2__*,TYPE_3__ const*) ; 
 scalar_t__ ngx_rtmp_receive_amf (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_cmd_play_init(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
        ngx_chain_t *in)
{
    static ngx_rtmp_play_t          v;

    static ngx_rtmp_amf_elt_t       in_elts[] = {

        /* transaction is always 0 */
        { NGX_RTMP_AMF_NUMBER,
          ngx_null_string,
          NULL, 0 },

        { NGX_RTMP_AMF_NULL,
          ngx_null_string,
          NULL, 0 },

        { NGX_RTMP_AMF_STRING,
          ngx_null_string,
          &v.name, sizeof(v.name) },

        { NGX_RTMP_AMF_OPTIONAL | NGX_RTMP_AMF_NUMBER,
          ngx_null_string,
          &v.start, 0 },

        { NGX_RTMP_AMF_OPTIONAL | NGX_RTMP_AMF_NUMBER,
          ngx_null_string,
          &v.duration, 0 },

        { NGX_RTMP_AMF_OPTIONAL | NGX_RTMP_AMF_BOOLEAN,
          ngx_null_string,
          &v.reset, 0 }
    };

    ngx_memzero(&v, sizeof(v));

    if (ngx_rtmp_receive_amf(s, in, in_elts,
                             sizeof(in_elts) / sizeof(in_elts[0])))
    {
        return NGX_ERROR;
    }

    ngx_rtmp_cmd_fill_args(v.name, v.args);

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
                  "play: name='%s' args='%s' start=%i duration=%i "
                  "reset=%i silent=%i",
                  v.name, v.args, (ngx_int_t) v.start,
                  (ngx_int_t) v.duration, (ngx_int_t) v.reset,
                  (ngx_int_t) v.silent);

    return ngx_rtmp_play(s, &v);
}