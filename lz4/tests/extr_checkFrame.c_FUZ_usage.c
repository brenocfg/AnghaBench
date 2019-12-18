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
 int /*<<< orphan*/  DISPLAY (char*,...) ; 

int FUZ_usage(const char* programName)
{
    DISPLAY( "Usage :\n");
    DISPLAY( "      %s [args] filename\n", programName);
    DISPLAY( "\n");
    DISPLAY( "Arguments :\n");
    DISPLAY( " -b#    : expected blocksizeID [4-7] (required)\n");
    DISPLAY( " -B#    : expected blocksize [32-4194304] (required)\n");
    DISPLAY( " -v     : verbose\n");
    DISPLAY( " -h     : display help and exit\n");
    return 0;
}