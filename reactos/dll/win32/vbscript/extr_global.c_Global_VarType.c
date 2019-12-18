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
typedef  int /*<<< orphan*/  vbdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int VT_TYPEMASK ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_short (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT Global_VarType(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    TRACE("(%s)\n", debugstr_variant(arg));

    assert(args_cnt == 1);

    if(V_VT(arg) & ~VT_TYPEMASK) {
        FIXME("not supported %s\n", debugstr_variant(arg));
        return E_NOTIMPL;
    }

    return return_short(res, V_VT(arg));
}