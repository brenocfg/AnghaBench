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
typedef  int D3D_SHADER_VARIABLE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_SVT_APPEND_STRUCTURED_BUFFER ; 
 int /*<<< orphan*/  D3D_SVT_BLEND ; 
 int /*<<< orphan*/  D3D_SVT_BOOL ; 
 int /*<<< orphan*/  D3D_SVT_BUFFER ; 
 int /*<<< orphan*/  D3D_SVT_BYTEADDRESS_BUFFER ; 
 int /*<<< orphan*/  D3D_SVT_CBUFFER ; 
 int /*<<< orphan*/  D3D_SVT_COMPUTESHADER ; 
 int /*<<< orphan*/  D3D_SVT_CONSUME_STRUCTURED_BUFFER ; 
 int /*<<< orphan*/  D3D_SVT_DEPTHSTENCIL ; 
 int /*<<< orphan*/  D3D_SVT_DEPTHSTENCILVIEW ; 
 int /*<<< orphan*/  D3D_SVT_DOMAINSHADER ; 
 int /*<<< orphan*/  D3D_SVT_DOUBLE ; 
 int /*<<< orphan*/  D3D_SVT_FLOAT ; 
 int /*<<< orphan*/  D3D_SVT_GEOMETRYSHADER ; 
 int /*<<< orphan*/  D3D_SVT_HULLSHADER ; 
 int /*<<< orphan*/  D3D_SVT_INT ; 
 int /*<<< orphan*/  D3D_SVT_INTERFACE_POINTER ; 
 int /*<<< orphan*/  D3D_SVT_PIXELSHADER ; 
 int /*<<< orphan*/  D3D_SVT_RASTERIZER ; 
 int /*<<< orphan*/  D3D_SVT_RENDERTARGETVIEW ; 
 int /*<<< orphan*/  D3D_SVT_RWBUFFER ; 
 int /*<<< orphan*/  D3D_SVT_RWBYTEADDRESS_BUFFER ; 
 int /*<<< orphan*/  D3D_SVT_RWSTRUCTURED_BUFFER ; 
 int /*<<< orphan*/  D3D_SVT_RWTEXTURE1D ; 
 int /*<<< orphan*/  D3D_SVT_RWTEXTURE1DARRAY ; 
 int /*<<< orphan*/  D3D_SVT_RWTEXTURE2D ; 
 int /*<<< orphan*/  D3D_SVT_RWTEXTURE2DARRAY ; 
 int /*<<< orphan*/  D3D_SVT_RWTEXTURE3D ; 
 int /*<<< orphan*/  D3D_SVT_SAMPLER ; 
 int /*<<< orphan*/  D3D_SVT_STRING ; 
 int /*<<< orphan*/  D3D_SVT_STRUCTURED_BUFFER ; 
 int /*<<< orphan*/  D3D_SVT_TBUFFER ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE1D ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE1DARRAY ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE2D ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE2DARRAY ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE2DMS ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE2DMSARRAY ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURE3D ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURECUBE ; 
 int /*<<< orphan*/  D3D_SVT_TEXTURECUBEARRAY ; 
 int /*<<< orphan*/  D3D_SVT_UINT ; 
 int /*<<< orphan*/  D3D_SVT_UINT8 ; 
 int /*<<< orphan*/  D3D_SVT_VERTEXSHADER ; 
 int /*<<< orphan*/  D3D_SVT_VOID ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_D3DCOMPILER_TO_STR (int /*<<< orphan*/ ) ; 

const char *debug_d3dcompiler_shader_variable_type(D3D_SHADER_VARIABLE_TYPE t)
{
    switch (t)
    {
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_VOID);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_BOOL);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_INT);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_FLOAT);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_STRING);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE1D);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE2D);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE3D);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURECUBE);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_SAMPLER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_PIXELSHADER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_VERTEXSHADER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_UINT);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_UINT8);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_GEOMETRYSHADER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RASTERIZER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_DEPTHSTENCIL);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_BLEND);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_BUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_CBUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TBUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE1DARRAY);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE2DARRAY);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RENDERTARGETVIEW);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_DEPTHSTENCILVIEW);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE2DMS);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURE2DMSARRAY);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_TEXTURECUBEARRAY);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_HULLSHADER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_DOMAINSHADER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_INTERFACE_POINTER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_COMPUTESHADER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_DOUBLE);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWTEXTURE1D);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWTEXTURE1DARRAY);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWTEXTURE2D);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWTEXTURE2DARRAY);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWTEXTURE3D);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWBUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_BYTEADDRESS_BUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWBYTEADDRESS_BUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_STRUCTURED_BUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_RWSTRUCTURED_BUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_APPEND_STRUCTURED_BUFFER);
        WINE_D3DCOMPILER_TO_STR(D3D_SVT_CONSUME_STRUCTURED_BUFFER);
        default:
            FIXME("Unrecognized D3D_SHADER_VARIABLE_TYPE %#x.\n", t);
            return "unrecognized";
    }
}