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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9_INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK_D3DDEVICE9 () ; 

__attribute__((used)) static HRESULT InvalidCall(LPDIRECT3DDEVICE9_INT This, LPSTR ErrorMsg)
{
    DPRINT1("%s",ErrorMsg);
    UNLOCK_D3DDEVICE9();
    return D3DERR_INVALIDCALL;
}