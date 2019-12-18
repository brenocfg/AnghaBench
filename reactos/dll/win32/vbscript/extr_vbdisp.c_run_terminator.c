#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int terminator_ran; int /*<<< orphan*/  ref; TYPE_2__* desc; } ;
typedef  TYPE_3__ vbdisp_t ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {size_t class_terminate_id; TYPE_1__* funcs; int /*<<< orphan*/  ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/ * entries; } ;
typedef  TYPE_4__ DISPPARAMS ;
typedef  int BOOL ;

/* Variables and functions */
 int TRUE ; 
 size_t VBDISP_CALLGET ; 
 int /*<<< orphan*/  exec_script (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL run_terminator(vbdisp_t *This)
{
    DISPPARAMS dp = {0};

    if(This->terminator_ran)
        return TRUE;
    This->terminator_ran = TRUE;

    if(!This->desc->class_terminate_id)
        return TRUE;

    This->ref++;
    exec_script(This->desc->ctx, This->desc->funcs[This->desc->class_terminate_id].entries[VBDISP_CALLGET],
            This, &dp, NULL);
    return !--This->ref;
}