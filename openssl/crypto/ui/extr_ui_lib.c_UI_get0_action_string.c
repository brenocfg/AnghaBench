#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* action_desc; } ;
struct TYPE_6__ {TYPE_1__ boolean_data; } ;
struct TYPE_7__ {int type; TYPE_2__ _; } ;
typedef  TYPE_3__ UI_STRING ;

/* Variables and functions */
#define  UIT_BOOLEAN 133 
#define  UIT_ERROR 132 
#define  UIT_INFO 131 
#define  UIT_NONE 130 
#define  UIT_PROMPT 129 
#define  UIT_VERIFY 128 

const char *UI_get0_action_string(UI_STRING *uis)
{
    switch (uis->type) {
    case UIT_BOOLEAN:
        return uis->_.boolean_data.action_desc;
    case UIT_PROMPT:
    case UIT_NONE:
    case UIT_VERIFY:
    case UIT_INFO:
    case UIT_ERROR:
        break;
    }
    return NULL;
}