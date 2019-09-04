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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/ * LPDIRECT3DTEXTURE9 ;
typedef  int /*<<< orphan*/ * LPD3D9MIPMAP ;

/* Variables and functions */
 int /*<<< orphan*/  D3D9MipMap ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpVtbl ; 

LPD3D9MIPMAP IDirect3DTexture9ToImpl(LPDIRECT3DTEXTURE9 iface)
{
    if (NULL == iface)
        return NULL;

    return (LPD3D9MIPMAP)((ULONG_PTR)iface - FIELD_OFFSET(D3D9MipMap, lpVtbl));
}