#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  texthost; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Run ;
typedef  int /*<<< orphan*/  ME_Context ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_TxGetDC (int /*<<< orphan*/ ) ; 
 int ME_CharFromPointContext (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_DestroyContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_InitContext (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

int ME_CharFromPoint(ME_TextEditor *editor, int cx, ME_Run *run, BOOL closest, BOOL visual_order)
{
    ME_Context c;
    int ret;

    ME_InitContext( &c, editor, ITextHost_TxGetDC( editor->texthost ) );
    ret = ME_CharFromPointContext( &c, cx, run, closest, visual_order );
    ME_DestroyContext(&c);
    return ret;
}