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
struct spirv_compiler {TYPE_1__* fns; } ;
struct ra_d3d11 {scalar_t__ fl; int /*<<< orphan*/  (* D3DCompile ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ;struct spirv_compiler* spirv; } ;
struct ra {int /*<<< orphan*/  log; struct ra_d3d11* priv; } ;
typedef  scalar_t__ spvc_result ;
typedef  int /*<<< orphan*/ * spvc_parsed_ir ;
typedef  int /*<<< orphan*/ * spvc_context ;
typedef  int /*<<< orphan*/ * spvc_compiler_options ;
typedef  int /*<<< orphan*/ * spvc_compiler ;
typedef  scalar_t__ int64_t ;
typedef  enum glsl_shader { ____Placeholder_glsl_shader } glsl_shader ;
struct TYPE_5__ {int len; scalar_t__ start; } ;
typedef  TYPE_2__ bstr ;
struct TYPE_4__ {int /*<<< orphan*/  (* compile_glsl ) (struct spirv_compiler*,void*,int,char const*,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  SpvId ;
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCOMPILE_OPTIMIZATION_LEVEL3 ; 
 scalar_t__ D3D_FEATURE_LEVEL_10_1 ; 
 scalar_t__ D3D_FEATURE_LEVEL_11_0 ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int GLSL_SHADER_VERTEX ; 
 scalar_t__ ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 scalar_t__ ID3D10Blob_GetBufferSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_ERR (struct ra*,char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  MP_MSG (struct ra*,int,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra*,char*,scalar_t__,scalar_t__,...) ; 
 int MSGL_DEBUG ; 
 int MSGL_ERR ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPVC_BACKEND_HLSL ; 
 int /*<<< orphan*/  SPVC_CAPTURE_MODE_TAKE_OWNERSHIP ; 
 int /*<<< orphan*/  SPVC_COMPILER_OPTION_FLIP_VERTEX_Y ; 
 int /*<<< orphan*/  SPVC_COMPILER_OPTION_HLSL_SHADER_MODEL ; 
 scalar_t__ SPVC_SUCCESS ; 
 int /*<<< orphan*/  SPVC_TRUE ; 
 int /*<<< orphan*/  get_shader_target (struct ra*,int) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_log_source (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  shader_type_name (int) ; 
 scalar_t__ spvc_compiler_compile (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ spvc_compiler_create_compiler_options (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ spvc_compiler_install_compiler_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ spvc_compiler_options_set_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spvc_compiler_options_set_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ spvc_context_create (int /*<<< orphan*/ **) ; 
 scalar_t__ spvc_context_create_compiler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spvc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spvc_context_get_last_error_string (int /*<<< orphan*/ *) ; 
 scalar_t__ spvc_context_parse_spirv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct spirv_compiler*,void*,int,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool compile_glsl(struct ra *ra, enum glsl_shader type,
                         const char *glsl, ID3DBlob **out)
{
    struct ra_d3d11 *p = ra->priv;
    struct spirv_compiler *spirv = p->spirv;
    void *ta_ctx = talloc_new(NULL);
    spvc_result sc_res = SPVC_SUCCESS;
    spvc_context sc_ctx = NULL;
    spvc_parsed_ir sc_ir = NULL;
    spvc_compiler sc_compiler = NULL;
    spvc_compiler_options sc_opts = NULL;
    const char *hlsl = NULL;
    ID3DBlob *errors = NULL;
    bool success = false;
    HRESULT hr;

    int sc_shader_model;
    if (p->fl >= D3D_FEATURE_LEVEL_11_0) {
        sc_shader_model = 50;
    } else if (p->fl >= D3D_FEATURE_LEVEL_10_1) {
        sc_shader_model = 41;
    } else {
        sc_shader_model = 40;
    }

    int64_t start_us = mp_time_us();

    bstr spv_module;
    if (!spirv->fns->compile_glsl(spirv, ta_ctx, type, glsl, &spv_module))
        goto done;

    int64_t shaderc_us = mp_time_us();

    sc_res = spvc_context_create(&sc_ctx);
    if (sc_res != SPVC_SUCCESS)
        goto done;

    sc_res = spvc_context_parse_spirv(sc_ctx, (SpvId *)spv_module.start,
                                      spv_module.len / sizeof(SpvId), &sc_ir);
    if (sc_res != SPVC_SUCCESS)
        goto done;

    sc_res = spvc_context_create_compiler(sc_ctx, SPVC_BACKEND_HLSL, sc_ir,
                                          SPVC_CAPTURE_MODE_TAKE_OWNERSHIP,
                                          &sc_compiler);
    if (sc_res != SPVC_SUCCESS)
        goto done;

    sc_res = spvc_compiler_create_compiler_options(sc_compiler, &sc_opts);
    if (sc_res != SPVC_SUCCESS)
        goto done;
    sc_res = spvc_compiler_options_set_uint(sc_opts,
        SPVC_COMPILER_OPTION_HLSL_SHADER_MODEL, sc_shader_model);
    if (sc_res != SPVC_SUCCESS)
        goto done;
    if (type == GLSL_SHADER_VERTEX) {
        // FLIP_VERTEX_Y is only valid for vertex shaders
        sc_res = spvc_compiler_options_set_bool(sc_opts,
            SPVC_COMPILER_OPTION_FLIP_VERTEX_Y, SPVC_TRUE);
        if (sc_res != SPVC_SUCCESS)
            goto done;
    }
    sc_res = spvc_compiler_install_compiler_options(sc_compiler, sc_opts);
    if (sc_res != SPVC_SUCCESS)
        goto done;

    sc_res = spvc_compiler_compile(sc_compiler, &hlsl);
    if (sc_res != SPVC_SUCCESS)
        goto done;

    int64_t cross_us = mp_time_us();

    hr = p->D3DCompile(hlsl, strlen(hlsl), NULL, NULL, NULL, "main",
        get_shader_target(ra, type), D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, out,
        &errors);
    if (FAILED(hr)) {
        MP_ERR(ra, "D3DCompile failed: %s\n%.*s", mp_HRESULT_to_str(hr),
               (int)ID3D10Blob_GetBufferSize(errors),
               (char*)ID3D10Blob_GetBufferPointer(errors));
        goto done;
    }

    int64_t d3dcompile_us = mp_time_us();

    MP_VERBOSE(ra, "Compiled a %s shader in %lldus\n", shader_type_name(type),
               d3dcompile_us - start_us);
    MP_VERBOSE(ra, "shaderc: %lldus, SPIRV-Cross: %lldus, D3DCompile: %lldus\n",
               shaderc_us - start_us,
               cross_us - shaderc_us,
               d3dcompile_us - cross_us);

    success = true;
done:
    if (sc_res != SPVC_SUCCESS) {
        MP_MSG(ra, MSGL_ERR, "SPIRV-Cross failed: %s\n",
               spvc_context_get_last_error_string(sc_ctx));
    }
    int level = success ? MSGL_DEBUG : MSGL_ERR;
    MP_MSG(ra, level, "GLSL source:\n");
    mp_log_source(ra->log, level, glsl);
    if (hlsl) {
        MP_MSG(ra, level, "HLSL source:\n");
        mp_log_source(ra->log, level, hlsl);
    }
    SAFE_RELEASE(errors);
    if (sc_ctx)
        spvc_context_destroy(sc_ctx);
    talloc_free(ta_ctx);
    return success;
}