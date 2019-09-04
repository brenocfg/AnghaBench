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
struct input_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 

int mp_event_get_mime_type_score(struct input_ctx *ictx, const char *mime_type)
{
    // X11 and Wayland file list format.
    if (strcmp(mime_type, "text/uri-list") == 0)
        return 10;
    // Just text; treat it the same for convenience.
    if (strcmp(mime_type, "text/plain;charset=utf-8") == 0)
        return 5;
    if (strcmp(mime_type, "text/plain") == 0)
        return 4;
    if (strcmp(mime_type, "text") == 0)
        return 0;
    return -1;
}