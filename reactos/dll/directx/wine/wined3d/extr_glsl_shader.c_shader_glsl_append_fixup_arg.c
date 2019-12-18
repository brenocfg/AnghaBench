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
typedef  enum fixup_channel_source { ____Placeholder_fixup_channel_source } fixup_channel_source ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  CHANNEL_SOURCE_ONE 133 
#define  CHANNEL_SOURCE_W 132 
#define  CHANNEL_SOURCE_X 131 
#define  CHANNEL_SOURCE_Y 130 
#define  CHANNEL_SOURCE_Z 129 
#define  CHANNEL_SOURCE_ZERO 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 

__attribute__((used)) static void shader_glsl_append_fixup_arg(char *arguments, const char *reg_name,
        BOOL sign_fixup, enum fixup_channel_source channel_source)
{
    switch(channel_source)
    {
        case CHANNEL_SOURCE_ZERO:
            strcat(arguments, "0.0");
            break;

        case CHANNEL_SOURCE_ONE:
            strcat(arguments, "1.0");
            break;

        case CHANNEL_SOURCE_X:
            strcat(arguments, reg_name);
            strcat(arguments, ".x");
            break;

        case CHANNEL_SOURCE_Y:
            strcat(arguments, reg_name);
            strcat(arguments, ".y");
            break;

        case CHANNEL_SOURCE_Z:
            strcat(arguments, reg_name);
            strcat(arguments, ".z");
            break;

        case CHANNEL_SOURCE_W:
            strcat(arguments, reg_name);
            strcat(arguments, ".w");
            break;

        default:
            FIXME("Unhandled channel source %#x\n", channel_source);
            strcat(arguments, "undefined");
            break;
    }

    if (sign_fixup) strcat(arguments, " * 2.0 - 1.0");
}