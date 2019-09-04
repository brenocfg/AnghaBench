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
struct mp_log_root {scalar_t__ blank_lines; scalar_t__ status_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void flush_status_line(struct mp_log_root *root)
{
    // If there was a status line, don't overwrite it, but skip it.
    if (root->status_lines)
        fprintf(stderr, "\n");
    root->status_lines = 0;
    root->blank_lines = 0;
}