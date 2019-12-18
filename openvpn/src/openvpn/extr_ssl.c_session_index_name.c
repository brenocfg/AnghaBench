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
#define  TM_ACTIVE 130 
#define  TM_LAME_DUCK 129 
#define  TM_UNTRUSTED 128 

__attribute__((used)) static const char *
session_index_name(int index)
{
    switch (index)
    {
        case TM_ACTIVE:
            return "TM_ACTIVE";

        case TM_UNTRUSTED:
            return "TM_UNTRUSTED";

        case TM_LAME_DUCK:
            return "TM_LAME_DUCK";

        default:
            return "TM_???";
    }
}