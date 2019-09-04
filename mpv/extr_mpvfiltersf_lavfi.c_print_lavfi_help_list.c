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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_list (struct mp_log*,int) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*) ; 

void print_lavfi_help_list(struct mp_log *log, int media_type)
{
    dump_list(log, media_type);
    mp_info(log, "\nIf libavfilter filters clash with builtin mpv filters,\n"
            "prefix them with lavfi- to select the libavfilter one.\n\n");
}