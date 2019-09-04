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
 int /*<<< orphan*/  dlog_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int g_debug_level ; 

void print_hexbuf_no_asci(int level, unsigned char *title, unsigned char *buf, int len) 
{
    int j, k;
    if (level > g_debug_level) return;
    fprintf(dlog_file, "%s", title);
    for(j = 0, k = 0; j < len; j++, k++) {
        fprintf(dlog_file, "%02x ", buf[j]);
        if (((k+1) % 10 == 0 && k > 0)) {
            fprintf(dlog_file, "\n");
        }
    }
    fprintf(dlog_file, "\n");
}