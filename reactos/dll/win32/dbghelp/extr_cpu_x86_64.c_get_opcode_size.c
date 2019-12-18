#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int UnwindOp; int /*<<< orphan*/  OpInfo; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ UNWIND_CODE ;

/* Variables and functions */
#define  UWOP_ALLOC_LARGE 132 
#define  UWOP_SAVE_NONVOL 131 
#define  UWOP_SAVE_NONVOL_FAR 130 
#define  UWOP_SAVE_XMM128 129 
#define  UWOP_SAVE_XMM128_FAR 128 

__attribute__((used)) static int get_opcode_size(UNWIND_CODE op)
{
    switch (op.u.UnwindOp)
    {
    case UWOP_ALLOC_LARGE:
        return 2 + (op.u.OpInfo != 0);
    case UWOP_SAVE_NONVOL:
    case UWOP_SAVE_XMM128:
        return 2;
    case UWOP_SAVE_NONVOL_FAR:
    case UWOP_SAVE_XMM128_FAR:
        return 3;
    default:
        return 1;
    }
}