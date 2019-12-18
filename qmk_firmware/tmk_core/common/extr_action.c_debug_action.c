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
struct TYPE_4__ {int id; int param; } ;
struct TYPE_5__ {TYPE_1__ kind; } ;
typedef  TYPE_2__ action_t ;

/* Variables and functions */
#define  ACT_COMMAND 141 
#define  ACT_FUNCTION 140 
#define  ACT_LAYER 139 
#define  ACT_LAYER_MODS 138 
#define  ACT_LAYER_TAP 137 
#define  ACT_LAYER_TAP_EXT 136 
#define  ACT_LMODS 135 
#define  ACT_LMODS_TAP 134 
#define  ACT_MACRO 133 
#define  ACT_MOUSEKEY 132 
#define  ACT_RMODS 131 
#define  ACT_RMODS_TAP 130 
#define  ACT_SWAP_HANDS 129 
#define  ACT_USAGE 128 
 int /*<<< orphan*/  dprint (char*) ; 
 int /*<<< orphan*/  dprintf (char*,int,int) ; 

void debug_action(action_t action) {
    switch (action.kind.id) {
        case ACT_LMODS:
            dprint("ACT_LMODS");
            break;
        case ACT_RMODS:
            dprint("ACT_RMODS");
            break;
        case ACT_LMODS_TAP:
            dprint("ACT_LMODS_TAP");
            break;
        case ACT_RMODS_TAP:
            dprint("ACT_RMODS_TAP");
            break;
        case ACT_USAGE:
            dprint("ACT_USAGE");
            break;
        case ACT_MOUSEKEY:
            dprint("ACT_MOUSEKEY");
            break;
        case ACT_LAYER:
            dprint("ACT_LAYER");
            break;
        case ACT_LAYER_MODS:
            dprint("ACT_LAYER_MODS");
            break;
        case ACT_LAYER_TAP:
            dprint("ACT_LAYER_TAP");
            break;
        case ACT_LAYER_TAP_EXT:
            dprint("ACT_LAYER_TAP_EXT");
            break;
        case ACT_MACRO:
            dprint("ACT_MACRO");
            break;
        case ACT_COMMAND:
            dprint("ACT_COMMAND");
            break;
        case ACT_FUNCTION:
            dprint("ACT_FUNCTION");
            break;
        case ACT_SWAP_HANDS:
            dprint("ACT_SWAP_HANDS");
            break;
        default:
            dprint("UNKNOWN");
            break;
    }
    dprintf("[%X:%02X]", action.kind.param >> 8, action.kind.param & 0xff);
}