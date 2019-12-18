#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vaapi_opts {int /*<<< orphan*/  path; } ;
struct mpv_global {int dummy; } ;
struct TYPE_3__ {struct AVBufferRef* av_device_ref; } ;
struct mp_vaapi_ctx {TYPE_1__ hwctx; int /*<<< orphan*/  (* destroy_native_ctx ) (void*) ;void* native_ctx; } ;
struct mp_log {int dummy; } ;
struct hwcontext_create_dev_params {int /*<<< orphan*/  probing; } ;
struct AVBufferRef {int dummy; } ;
typedef  int /*<<< orphan*/  VADisplay ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (void*) ;int /*<<< orphan*/  (* create ) (int /*<<< orphan*/ **,void**,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct vaapi_opts* mp_get_config_group (int /*<<< orphan*/ *,struct mpv_global*,int /*<<< orphan*/ *) ; 
 TYPE_2__** native_displays ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  talloc_free (struct vaapi_opts*) ; 
 int /*<<< orphan*/  vaTerminate (int /*<<< orphan*/ *) ; 
 struct mp_vaapi_ctx* va_initialize (int /*<<< orphan*/ *,struct mp_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaapi_conf ; 

__attribute__((used)) static struct AVBufferRef *va_create_standalone(struct mpv_global *global,
        struct mp_log *log, struct hwcontext_create_dev_params *params)
{
    struct AVBufferRef *ret = NULL;
    struct vaapi_opts *opts = mp_get_config_group(NULL, global, &vaapi_conf);

    for (int n = 0; native_displays[n]; n++) {
        VADisplay *display = NULL;
        void *native_ctx = NULL;
        native_displays[n]->create(&display, &native_ctx, opts->path);
        if (display) {
            struct mp_vaapi_ctx *ctx =
                va_initialize(display, log, params->probing);
            if (!ctx) {
                vaTerminate(display);
                native_displays[n]->destroy(native_ctx);
                goto end;
            }
            ctx->native_ctx = native_ctx;
            ctx->destroy_native_ctx = native_displays[n]->destroy;
            ret = ctx->hwctx.av_device_ref;
            goto end;
        }
    }

end:
    talloc_free(opts);
    return ret;
}