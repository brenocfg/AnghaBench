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
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_GetStoryLength (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_SetEnd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ITextRange_SetStart (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  S_OK ; 
#define  tomStory 128 

__attribute__((used)) static HRESULT textrange_expand(ITextRange *range, LONG unit, LONG *delta)
{
    LONG expand_start, expand_end;

    switch (unit)
    {
    case tomStory:
        expand_start = 0;
        ITextRange_GetStoryLength(range, &expand_end);
        break;
    default:
        FIXME("unit %d is not supported\n", unit);
        return E_NOTIMPL;
    }

    if (delta) {
        LONG start, end;

        ITextRange_GetStart(range, &start);
        ITextRange_GetEnd(range, &end);
        *delta = expand_end - expand_start - (end - start);
    }

    ITextRange_SetStart(range, expand_start);
    ITextRange_SetEnd(range, expand_end);

    return S_OK;
}