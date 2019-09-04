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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

void osd_get_function_sym(char *buffer, size_t buffer_size, int osd_function)
{
    // 0xFF is never valid UTF-8, so we can use it to escape OSD symbols.
    // (Same trick as OSD_ASS_0/OSD_ASS_1.)
    snprintf(buffer, buffer_size, "\xFF%c", osd_function);
}