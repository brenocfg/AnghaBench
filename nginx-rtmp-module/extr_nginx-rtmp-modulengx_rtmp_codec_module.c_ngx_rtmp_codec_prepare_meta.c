#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  type; int /*<<< orphan*/  msid; int /*<<< orphan*/  csid; } ;
typedef  TYPE_1__ ngx_rtmp_header_t ;
struct TYPE_7__ {int /*<<< orphan*/  meta_version; int /*<<< orphan*/  meta; } ;
typedef  TYPE_2__ ngx_rtmp_codec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  h ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_CSID_AMF ; 
 int /*<<< orphan*/  NGX_RTMP_MSG_AMF_META ; 
 int /*<<< orphan*/  NGX_RTMP_MSID ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_get_next_version () ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_prepare_message (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_codec_prepare_meta(ngx_rtmp_session_t *s, uint32_t timestamp)
{
    ngx_rtmp_header_t      h;
    ngx_rtmp_codec_ctx_t  *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    ngx_memzero(&h, sizeof(h));
    h.csid = NGX_RTMP_CSID_AMF;
    h.msid = NGX_RTMP_MSID;
    h.type = NGX_RTMP_MSG_AMF_META;
    h.timestamp = timestamp;
    ngx_rtmp_prepare_message(s, &h, NULL, ctx->meta);

    ctx->meta_version = ngx_rtmp_codec_get_next_version();

    return NGX_OK;
}