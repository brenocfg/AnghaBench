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
struct ra_hwdec {int /*<<< orphan*/  global; int /*<<< orphan*/  ra; struct cuda_hw_priv* priv; } ;
struct cuda_hw_priv {int do_full_sync; int /*<<< orphan*/  ext_uninit; int /*<<< orphan*/  ext_init; int /*<<< orphan*/  decode_ctx; int /*<<< orphan*/  display_ctx; TYPE_2__* cu; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cuCtxCreate ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* cuCtxPopCurrent ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cuDeviceGet ) (scalar_t__*,int) ;int /*<<< orphan*/  (* cuGLGetDevices ) (unsigned int*,scalar_t__*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int version; int es; } ;
typedef  TYPE_1__ GL ;
typedef  TYPE_2__ CudaFunctions ;
typedef  scalar_t__ CUdevice ;
typedef  int /*<<< orphan*/  CUcontext ;

/* Variables and functions */
 int CHECK_CU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CU_CTX_SCHED_BLOCKING_SYNC ; 
 int /*<<< orphan*/  CU_GL_DEVICE_LIST_ALL ; 
 int /*<<< orphan*/  MP_INFO (struct ra_hwdec const*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_hwdec const*,char*) ; 
 int /*<<< orphan*/  cuda_ext_gl_init ; 
 int /*<<< orphan*/  cuda_ext_gl_uninit ; 
 int /*<<< orphan*/  m_option_type_choice ; 
 int /*<<< orphan*/  mp_read_option_raw (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* ra_gl_get (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_is_gl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned int*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

bool cuda_gl_init(const struct ra_hwdec *hw) {
    int ret = 0;
    struct cuda_hw_priv *p = hw->priv;
    CudaFunctions *cu = p->cu;

    if (ra_is_gl(hw->ra)) {
        GL *gl = ra_gl_get(hw->ra);
        if (gl->version < 210 && gl->es < 300) {
            MP_VERBOSE(hw, "need OpenGL >= 2.1 or OpenGL-ES >= 3.0\n");
            return false;
        }
    } else {
        // This is not an OpenGL RA.
        return false;
    }

    CUdevice display_dev;
    unsigned int device_count;
    ret = CHECK_CU(cu->cuGLGetDevices(&device_count, &display_dev, 1,
                                      CU_GL_DEVICE_LIST_ALL));
    if (ret < 0)
        return false;

    ret = CHECK_CU(cu->cuCtxCreate(&p->display_ctx, CU_CTX_SCHED_BLOCKING_SYNC,
                                   display_dev));
    if (ret < 0)
        return false;

    p->decode_ctx = p->display_ctx;

    int decode_dev_idx = -1;
    mp_read_option_raw(hw->global, "cuda-decode-device", &m_option_type_choice,
                       &decode_dev_idx);

    if (decode_dev_idx > -1) {
        CUcontext dummy;
        CUdevice decode_dev;
        ret = CHECK_CU(cu->cuDeviceGet(&decode_dev, decode_dev_idx));
        if (ret < 0) {
            CHECK_CU(cu->cuCtxPopCurrent(&dummy));
            return false;
        }

        if (decode_dev != display_dev) {
            MP_INFO(hw, "Using separate decoder and display devices\n");

            // Pop the display context. We won't use it again during init()
            ret = CHECK_CU(cu->cuCtxPopCurrent(&dummy));
            if (ret < 0)
                return false;

            ret = CHECK_CU(cu->cuCtxCreate(&p->decode_ctx, CU_CTX_SCHED_BLOCKING_SYNC,
                                           decode_dev));
            if (ret < 0)
                return false;
        }
    }

    // We don't have a way to do a GPU sync after copying
    p->do_full_sync = true;

    p->ext_init = cuda_ext_gl_init;
    p->ext_uninit = cuda_ext_gl_uninit;

    return true;
}