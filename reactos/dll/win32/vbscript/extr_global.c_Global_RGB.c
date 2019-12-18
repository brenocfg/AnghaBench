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
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_VBSERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VBSE_ILLEGAL_FUNC_CALL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_int (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static HRESULT Global_RGB(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    HRESULT hres;
    int i, color[3];

    TRACE("%s %s %s\n", debugstr_variant(arg), debugstr_variant(arg + 1), debugstr_variant(arg + 2));

    assert(args_cnt == 3);

    for(i = 0; i < 3; i++) {
        hres = to_int(arg + i, color + i);
        if(FAILED(hres))
            return hres;
        if(color[i] > 255)
            color[i] = 255;
        if(color[i] < 0)
            return MAKE_VBSERROR(VBSE_ILLEGAL_FUNC_CALL);
    }

    return return_int(res, RGB(color[0], color[1], color[2]));
}