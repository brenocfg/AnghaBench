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
typedef  int D3DXPARAMETER_CLASS ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXPC_MATRIX_COLUMNS ; 
 int /*<<< orphan*/  D3DXPC_MATRIX_ROWS ; 
 int /*<<< orphan*/  D3DXPC_OBJECT ; 
 int /*<<< orphan*/  D3DXPC_SCALAR ; 
 int /*<<< orphan*/  D3DXPC_STRUCT ; 
 int /*<<< orphan*/  D3DXPC_VECTOR ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_D3DX_TO_STR (int /*<<< orphan*/ ) ; 

const char *debug_d3dxparameter_class(D3DXPARAMETER_CLASS c)
{
    switch (c)
    {
        WINE_D3DX_TO_STR(D3DXPC_SCALAR);
        WINE_D3DX_TO_STR(D3DXPC_VECTOR);
        WINE_D3DX_TO_STR(D3DXPC_MATRIX_ROWS);
        WINE_D3DX_TO_STR(D3DXPC_MATRIX_COLUMNS);
        WINE_D3DX_TO_STR(D3DXPC_OBJECT);
        WINE_D3DX_TO_STR(D3DXPC_STRUCT);
        default:
            FIXME("Unrecognized D3DXPARAMETER_CLASS %#x.\n", c);
            return "unrecognized";
    }
}