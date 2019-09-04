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
struct vo {int /*<<< orphan*/  hwdec_devs; int /*<<< orphan*/  osd; int /*<<< orphan*/  global; int /*<<< orphan*/  log; struct gpu_priv* priv; } ;
struct ra_ctx_opts {int want_alpha; } ;
struct gpu_priv {int /*<<< orphan*/  renderer; TYPE_1__* ctx; int /*<<< orphan*/  context_name; int /*<<< orphan*/  context_type; struct ra_ctx_opts opts; int /*<<< orphan*/  log; } ;
struct TYPE_2__ {int /*<<< orphan*/  ra; int /*<<< orphan*/  swapchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_request_hwdec_api ; 
 int /*<<< orphan*/  get_and_update_icc_profile (struct gpu_priv*) ; 
 int /*<<< orphan*/  gl_video_configure_queue (int /*<<< orphan*/ ,struct vo*) ; 
 int /*<<< orphan*/  gl_video_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_video_load_hwdecs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_video_set_osd_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwdec_devices_create () ; 
 int /*<<< orphan*/  hwdec_devices_set_loader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vo*) ; 
 int /*<<< orphan*/  m_option_type_choice ; 
 int /*<<< orphan*/  mp_read_option_raw (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* ra_ctx_create (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ra_ctx_opts) ; 
 int /*<<< orphan*/  uninit (struct vo*) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    struct gpu_priv *p = vo->priv;
    p->log = vo->log;

    int alpha_mode;
    mp_read_option_raw(vo->global, "alpha", &m_option_type_choice, &alpha_mode);

    struct ra_ctx_opts opts = p->opts;
    opts.want_alpha = alpha_mode == 1;

    p->ctx = ra_ctx_create(vo, p->context_type, p->context_name, opts);
    if (!p->ctx)
        goto err_out;
    assert(p->ctx->ra);
    assert(p->ctx->swapchain);

    p->renderer = gl_video_init(p->ctx->ra, vo->log, vo->global);
    gl_video_set_osd_source(p->renderer, vo->osd);
    gl_video_configure_queue(p->renderer, vo);

    get_and_update_icc_profile(p);

    vo->hwdec_devs = hwdec_devices_create();
    hwdec_devices_set_loader(vo->hwdec_devs, call_request_hwdec_api, vo);

    gl_video_load_hwdecs(p->renderer, vo->hwdec_devs, false);

    return 0;

err_out:
    uninit(vo);
    return -1;
}