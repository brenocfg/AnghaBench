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
typedef  int DWORD ;

/* Variables and functions */
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  dlog_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int g_debug_level ; 

void print_share_mode(int level, DWORD mode)
{
    if (level > g_debug_level) return;
    fprintf(dlog_file, "share mode: ");
    if (mode & FILE_SHARE_READ)
        fprintf(dlog_file, "READ ");
    if (mode & FILE_SHARE_WRITE)
        fprintf(dlog_file, "WRITE ");
    if (mode & FILE_SHARE_DELETE)
        fprintf(dlog_file, "DELETE");
    fprintf(dlog_file, "\n");
}