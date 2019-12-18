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
typedef  int D3DXREGISTER_SET ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXRS_BOOL ; 
 int /*<<< orphan*/  D3DXRS_FLOAT4 ; 
 int /*<<< orphan*/  D3DXRS_INT4 ; 
 int /*<<< orphan*/  D3DXRS_SAMPLER ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_D3DX_TO_STR (int /*<<< orphan*/ ) ; 

const char *debug_d3dxparameter_registerset(D3DXREGISTER_SET r)
{
    switch (r)
    {
        WINE_D3DX_TO_STR(D3DXRS_BOOL);
        WINE_D3DX_TO_STR(D3DXRS_INT4);
        WINE_D3DX_TO_STR(D3DXRS_FLOAT4);
        WINE_D3DX_TO_STR(D3DXRS_SAMPLER);
        default:
            FIXME("Unrecognized D3DXREGISTER_SET %#x.\n", r);
            return "unrecognized";
    }
}