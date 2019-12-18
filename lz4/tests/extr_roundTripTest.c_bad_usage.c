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
 int /*<<< orphan*/  MSG (char*,...) ; 

int bad_usage(const char* exeName)
{
    MSG(" \n");
    MSG("bad usage: \n");
    MSG(" \n");
    MSG("%s [Options] fileName \n", exeName);
    MSG(" \n");
    MSG("Options: \n");
    MSG("-#     : use #=[0-9] compression level (default:0 == random) \n");
    return 1;
}