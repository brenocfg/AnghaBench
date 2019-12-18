#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_header_t ;
struct TYPE_11__ {char* app; char* flashver; char* swf_url; char* tc_url; char acodecs; char vcodecs; char* page_url; char object_encoding; char trans; int /*<<< orphan*/  args; } ;
typedef  TYPE_3__ ngx_rtmp_connect_t ;
typedef  char ngx_rtmp_amf_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  in_elts ;
typedef  int /*<<< orphan*/  in_cmd ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
#define  NGX_RTMP_AMF_NUMBER 131 
#define  NGX_RTMP_AMF_OBJECT 130 
#define  NGX_RTMP_AMF_STRING 129 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__ const*,int) ; 
#define  ngx_null_string 128 
 int /*<<< orphan*/  ngx_rtmp_cmd_fill_args (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_connect (TYPE_2__*,TYPE_3__ const*) ; 
 scalar_t__ ngx_rtmp_receive_amf (TYPE_2__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  const ngx_string (char*) ; 
 size_t ngx_strlen (char*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_cmd_connect_init(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
        ngx_chain_t *in)
{
    size_t                      len;

    static ngx_rtmp_connect_t   v;

    static ngx_rtmp_amf_elt_t  in_cmd[] = {

        { NGX_RTMP_AMF_STRING,
          ngx_string("app"),
          v.app, sizeof(v.app) },

        { NGX_RTMP_AMF_STRING,
          ngx_string("flashVer"),
          v.flashver, sizeof(v.flashver) },

        { NGX_RTMP_AMF_STRING,
          ngx_string("swfUrl"),
          v.swf_url, sizeof(v.swf_url) },

        { NGX_RTMP_AMF_STRING,
          ngx_string("tcUrl"),
          v.tc_url, sizeof(v.tc_url) },

        { NGX_RTMP_AMF_NUMBER,
          ngx_string("audioCodecs"),
          &v.acodecs, sizeof(v.acodecs) },

        { NGX_RTMP_AMF_NUMBER,
          ngx_string("videoCodecs"),
          &v.vcodecs, sizeof(v.vcodecs) },

        { NGX_RTMP_AMF_STRING,
          ngx_string("pageUrl"),
          v.page_url, sizeof(v.page_url) },

        { NGX_RTMP_AMF_NUMBER,
          ngx_string("objectEncoding"),
          &v.object_encoding, 0},
    };

    static ngx_rtmp_amf_elt_t  in_elts[] = {

        { NGX_RTMP_AMF_NUMBER,
          ngx_null_string,
          &v.trans, 0 },

        { NGX_RTMP_AMF_OBJECT,
          ngx_null_string,
          in_cmd, sizeof(in_cmd) },
    };

    ngx_memzero(&v, sizeof(v));
    if (ngx_rtmp_receive_amf(s, in, in_elts,
                sizeof(in_elts) / sizeof(in_elts[0])))
    {
        return NGX_ERROR;
    }

    len = ngx_strlen(v.app);
    if (len > 10 && !ngx_memcmp(v.app + len - 10, "/_definst_", 10)) {
        v.app[len - 10] = 0;
    } else if (len && v.app[len - 1] == '/') {
        v.app[len - 1] = 0;
    }

    ngx_rtmp_cmd_fill_args(v.app, v.args);

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
            "connect: app='%s' args='%s' flashver='%s' swf_url='%s' "
            "tc_url='%s' page_url='%s' acodecs=%uD vcodecs=%uD "
            "object_encoding=%ui",
            v.app, v.args, v.flashver, v.swf_url, v.tc_url, v.page_url,
            (uint32_t)v.acodecs, (uint32_t)v.vcodecs,
            (ngx_int_t)v.object_encoding);

    return ngx_rtmp_connect(s, &v);
}