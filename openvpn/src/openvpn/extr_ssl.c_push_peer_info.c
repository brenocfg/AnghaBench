#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tls_session {TYPE_1__* opt; } ;
struct route_gateway_info {int flags; int /*<<< orphan*/  hwaddr; } ;
struct gc_arena {int dummy; } ;
struct env_set {struct env_item* list; } ;
struct env_item {scalar_t__ string; struct env_item* next; } ;
struct buffer {int dummy; } ;
struct TYPE_2__ {int push_peer_info_detail; scalar_t__ mode; int /*<<< orphan*/  net_ctx; int /*<<< orphan*/  comp_options; scalar_t__ pull; scalar_t__ ncp_enabled; struct env_set* es; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 scalar_t__ MODE_SERVER ; 
 scalar_t__ PACKAGE_VERSION ; 
 int RGI_HWADDR_DEFINED ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 
 scalar_t__ buf_safe (struct buffer*,scalar_t__) ; 
 int /*<<< orphan*/  comp_generate_peer_info_string (int /*<<< orphan*/ *,struct buffer*) ; 
 scalar_t__ format_hex_ex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char*,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  get_default_gateway (struct route_gateway_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_ssl_library_version () ; 
 scalar_t__ strlen (scalar_t__) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 scalar_t__ win32_version_string (struct gc_arena*,int) ; 
 int /*<<< orphan*/  write_empty_string (struct buffer*) ; 
 int /*<<< orphan*/  write_string (struct buffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
push_peer_info(struct buffer *buf, struct tls_session *session)
{
    struct gc_arena gc = gc_new();
    bool ret = false;

    if (session->opt->push_peer_info_detail > 0)
    {
        struct env_set *es = session->opt->es;
        struct env_item *e;
        struct buffer out = alloc_buf_gc(512*3, &gc);

        /* push version */
        buf_printf(&out, "IV_VER=%s\n", PACKAGE_VERSION);

        /* push platform */
#if defined(TARGET_LINUX)
        buf_printf(&out, "IV_PLAT=linux\n");
#elif defined(TARGET_SOLARIS)
        buf_printf(&out, "IV_PLAT=solaris\n");
#elif defined(TARGET_OPENBSD)
        buf_printf(&out, "IV_PLAT=openbsd\n");
#elif defined(TARGET_DARWIN)
        buf_printf(&out, "IV_PLAT=mac\n");
#elif defined(TARGET_NETBSD)
        buf_printf(&out, "IV_PLAT=netbsd\n");
#elif defined(TARGET_FREEBSD)
        buf_printf(&out, "IV_PLAT=freebsd\n");
#elif defined(TARGET_ANDROID)
        buf_printf(&out, "IV_PLAT=android\n");
#elif defined(_WIN32)
        buf_printf(&out, "IV_PLAT=win\n");
#endif

        /* support for P_DATA_V2 */
        buf_printf(&out, "IV_PROTO=2\n");

        /* support for Negotiable Crypto Parameters */
        if (session->opt->ncp_enabled
            && (session->opt->mode == MODE_SERVER || session->opt->pull))
        {
            buf_printf(&out, "IV_NCP=2\n");
        }

        /* push compression status */
#ifdef USE_COMP
        comp_generate_peer_info_string(&session->opt->comp_options, &out);
#endif

        if (session->opt->push_peer_info_detail >= 2)
        {
            /* push mac addr */
            struct route_gateway_info rgi;
            get_default_gateway(&rgi, session->opt->net_ctx);
            if (rgi.flags & RGI_HWADDR_DEFINED)
            {
                buf_printf(&out, "IV_HWADDR=%s\n", format_hex_ex(rgi.hwaddr, 6, 0, 1, ":", &gc));
            }
            buf_printf(&out, "IV_SSL=%s\n", get_ssl_library_version() );
#if defined(_WIN32)
            buf_printf(&out, "IV_PLAT_VER=%s\n", win32_version_string(&gc, false));
#endif
        }

        /* push env vars that begin with UV_, IV_PLAT_VER and IV_GUI_VER */
        for (e = es->list; e != NULL; e = e->next)
        {
            if (e->string)
            {
                if ((((strncmp(e->string, "UV_", 3)==0
                       || strncmp(e->string, "IV_PLAT_VER=", sizeof("IV_PLAT_VER=")-1)==0)
                      && session->opt->push_peer_info_detail >= 2)
                     || (strncmp(e->string,"IV_GUI_VER=",sizeof("IV_GUI_VER=")-1)==0))
                    && buf_safe(&out, strlen(e->string)+1))
                {
                    buf_printf(&out, "%s\n", e->string);
                }
            }
        }

        if (!write_string(buf, BSTR(&out), -1))
        {
            goto error;
        }
    }
    else
    {
        if (!write_empty_string(buf)) /* no peer info */
        {
            goto error;
        }
    }
    ret = true;

error:
    gc_free(&gc);
    return ret;
}