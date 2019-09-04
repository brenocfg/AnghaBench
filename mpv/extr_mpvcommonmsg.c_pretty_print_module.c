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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  set_msg_color (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_term_color (int /*<<< orphan*/ *,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void pretty_print_module(FILE* stream, const char *prefix, bool use_color, int lev)
{
    // Use random color based on the name of the module
    if (use_color) {
        size_t prefix_len = strlen(prefix);
        unsigned int mod = 0;
        for (int i = 0; i < prefix_len; ++i)
            mod = mod * 33 + prefix[i];
        set_term_color(stream, (mod + 1) % 15 + 1);
    }

    fprintf(stream, "%10s", prefix);
    if (use_color)
        set_term_color(stream, -1);
    fprintf(stream, ": ");
    if (use_color)
        set_msg_color(stream, lev);
}