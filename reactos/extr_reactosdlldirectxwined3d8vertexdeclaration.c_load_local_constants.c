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
struct wined3d_shader {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int const D3DVSD_CONSTADDRESSMASK ; 
 int const D3DVSD_CONSTADDRESSSHIFT ; 
 int const D3DVSD_CONSTCOUNTMASK ; 
 int const D3DVSD_CONSTCOUNTSHIFT ; 
 int const D3DVSD_END () ; 
 int const D3DVSD_TOKENTYPEMASK ; 
 int const D3DVSD_TOKENTYPESHIFT ; 
 int const D3DVSD_TOKEN_CONSTMEM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,float const,float const,float const,float const) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8 ; 
 int /*<<< orphan*/  parse_token (int const*) ; 
 int /*<<< orphan*/  wined3d_shader_set_local_constants_float (struct wined3d_shader*,int,float const*,int) ; 

void load_local_constants(const DWORD *d3d8_elements, struct wined3d_shader *wined3d_vertex_shader)
{
    const DWORD *token = d3d8_elements;

    while (*token != D3DVSD_END())
    {
        if (((*token & D3DVSD_TOKENTYPEMASK) >> D3DVSD_TOKENTYPESHIFT) == D3DVSD_TOKEN_CONSTMEM)
        {
            DWORD count = ((*token & D3DVSD_CONSTCOUNTMASK) >> D3DVSD_CONSTCOUNTSHIFT);
            DWORD constant_idx = ((*token & D3DVSD_CONSTADDRESSMASK) >> D3DVSD_CONSTADDRESSSHIFT);
            HRESULT hr;

            if (TRACE_ON(d3d8))
            {
                DWORD i;
                for (i = 0; i < count; ++i)
                {
                    TRACE("c[%u] = (%8f, %8f, %8f, %8f)\n",
                            constant_idx,
                            *(const float *)(token + i * 4 + 1),
                            *(const float *)(token + i * 4 + 2),
                            *(const float *)(token + i * 4 + 3),
                            *(const float *)(token + i * 4 + 4));
                }
            }
            hr = wined3d_shader_set_local_constants_float(wined3d_vertex_shader,
                    constant_idx, (const float *)token + 1, count);
            if (FAILED(hr)) ERR("Failed setting shader constants\n");
        }

        token += parse_token(token);
    }
}