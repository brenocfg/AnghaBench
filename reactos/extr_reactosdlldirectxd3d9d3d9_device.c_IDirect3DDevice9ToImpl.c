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
typedef  int /*<<< orphan*/ * LPDIRECT3DDEVICE9_INT ;
typedef  int /*<<< orphan*/ * LPDIRECT3DDEVICE9 ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECT3DDEVICE9_INT ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpVtbl ; 

LPDIRECT3DDEVICE9_INT IDirect3DDevice9ToImpl(LPDIRECT3DDEVICE9 iface)
{
    if (NULL == iface)
        return NULL;

    return (LPDIRECT3DDEVICE9_INT)((ULONG_PTR)iface - FIELD_OFFSET(DIRECT3DDEVICE9_INT, lpVtbl));
}