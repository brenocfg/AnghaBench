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

/* Variables and functions */
#define  S_ACTIVE 136 
#define  S_ERROR 135 
#define  S_GOT_KEY 134 
#define  S_INITIAL 133 
#define  S_NORMAL_OP 132 
#define  S_PRE_START 131 
#define  S_SENT_KEY 130 
#define  S_START 129 
#define  S_UNDEF 128 

__attribute__((used)) static const char *
state_name(int state)
{
    switch (state)
    {
        case S_UNDEF:
            return "S_UNDEF";

        case S_INITIAL:
            return "S_INITIAL";

        case S_PRE_START:
            return "S_PRE_START";

        case S_START:
            return "S_START";

        case S_SENT_KEY:
            return "S_SENT_KEY";

        case S_GOT_KEY:
            return "S_GOT_KEY";

        case S_ACTIVE:
            return "S_ACTIVE";

        case S_NORMAL_OP:
            return "S_NORMAL_OP";

        case S_ERROR:
            return "S_ERROR";

        default:
            return "S_???";
    }
}