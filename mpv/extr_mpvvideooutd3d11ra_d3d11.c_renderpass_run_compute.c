#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ra_renderpass_run_params {int /*<<< orphan*/ * compute_groups; struct ra_renderpass* pass; } ;
struct ra_renderpass {struct d3d_rpass* priv; } ;
struct ra_d3d11 {int /*<<< orphan*/  ctx; } ;
struct ra {struct ra_d3d11* priv; } ;
struct d3d_rpass {int /*<<< orphan*/  cs; } ;
typedef  int /*<<< orphan*/  ID3D11UnorderedAccessView ;
typedef  int /*<<< orphan*/  ID3D11ShaderResourceView ;
typedef  int /*<<< orphan*/  ID3D11SamplerState ;
typedef  int /*<<< orphan*/  ID3D11Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_CSSetConstantBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CSSetSamplers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CSSetShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CSSetShaderResources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CSSetUnorderedAccessViews (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renderpass_run_compute(struct ra *ra,
                                   const struct ra_renderpass_run_params *params,
                                   ID3D11Buffer *ubos[], int ubos_len,
                                   ID3D11SamplerState *samplers[],
                                   ID3D11ShaderResourceView *srvs[],
                                   int samplers_len,
                                   ID3D11UnorderedAccessView *uavs[],
                                   int uavs_len)
{
    struct ra_d3d11 *p = ra->priv;
    struct ra_renderpass *pass = params->pass;
    struct d3d_rpass *pass_p = pass->priv;

    ID3D11DeviceContext_CSSetShader(p->ctx, pass_p->cs, NULL, 0);
    ID3D11DeviceContext_CSSetConstantBuffers(p->ctx, 0, ubos_len, ubos);
    ID3D11DeviceContext_CSSetShaderResources(p->ctx, 0, samplers_len, srvs);
    ID3D11DeviceContext_CSSetSamplers(p->ctx, 0, samplers_len, samplers);
    ID3D11DeviceContext_CSSetUnorderedAccessViews(p->ctx, 0, uavs_len, uavs,
                                                  NULL);

    ID3D11DeviceContext_Dispatch(p->ctx, params->compute_groups[0],
                                         params->compute_groups[1],
                                         params->compute_groups[2]);

    for (int i = 0; i < ubos_len; i++)
        ubos[i] = NULL;
    for (int i = 0; i < samplers_len; i++) {
        samplers[i] = NULL;
        srvs[i] = NULL;
    }
    for (int i = 0; i < uavs_len; i++)
        uavs[i] = NULL;
    ID3D11DeviceContext_CSSetConstantBuffers(p->ctx, 0, ubos_len, ubos);
    ID3D11DeviceContext_CSSetShaderResources(p->ctx, 0, samplers_len, srvs);
    ID3D11DeviceContext_CSSetSamplers(p->ctx, 0, samplers_len, samplers);
    ID3D11DeviceContext_CSSetUnorderedAccessViews(p->ctx, 0, uavs_len, uavs,
                                                  NULL);
}