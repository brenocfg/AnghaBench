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
typedef  int D3D_SHADER_VARIABLE_CLASS ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_SVC_INTERFACE_CLASS ; 
 int /*<<< orphan*/  D3D_SVC_INTERFACE_POINTER ; 
 int /*<<< orphan*/  D3D_SVC_MATRIX_COLUMNS ; 
 int /*<<< orphan*/  D3D_SVC_MATRIX_ROWS ; 
 int /*<<< orphan*/  D3D_SVC_OBJECT ; 
 int /*<<< orphan*/  D3D_SVC_SCALAR ; 
 int /*<<< orphan*/  D3D_SVC_STRUCT ; 
 int /*<<< orphan*/  D3D_SVC_VECTOR ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_D3DCOMPILER_TO_STR (int /*<<< orphan*/ ) ; 

const char *debug_d3dcompiler_shader_variable_class(D3D_SHADER_VARIABLE_CLASS c)
{
    switch (c)
    {
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_SCALAR);
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_VECTOR);
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_MATRIX_ROWS);
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_MATRIX_COLUMNS);
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_OBJECT);
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_STRUCT);
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_INTERFACE_CLASS);
        WINE_D3DCOMPILER_TO_STR(D3D_SVC_INTERFACE_POINTER);
        default:
            FIXME("Unrecognized D3D_SHADER_VARIABLE_CLASS %#x.\n", c);
            return "unrecognized";
    }
}