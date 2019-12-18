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
 int FILE_APPEND_DATA ; 
 int FILE_DELETE_CHILD ; 
 int FILE_EXECUTE ; 
 int FILE_LIST_DIRECTORY ; 
 int FILE_READ_ATTRIBUTES ; 
 int FILE_READ_DATA ; 
 int FILE_READ_EA ; 
 int FILE_TRAVERSE ; 
 int FILE_WRITE_ATTRIBUTES ; 
 int FILE_WRITE_DATA ; 
 int FILE_WRITE_EA ; 
 int STANDARD_RIGHTS_READ ; 
 int STANDARD_RIGHTS_WRITE ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  dlog_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int g_debug_level ; 

void print_access_mask(int level, DWORD access_mask) {
    if (level > g_debug_level) return;
    fprintf(dlog_file, "access mask: ");
    if (access_mask & FILE_READ_DATA)
        fprintf(dlog_file, "READ ");
    if (access_mask & STANDARD_RIGHTS_READ)
        fprintf(dlog_file, "READ_ACL ");
    if (access_mask & FILE_READ_ATTRIBUTES)
        fprintf(dlog_file, "READ_ATTR ");
    if (access_mask & FILE_READ_EA)
        fprintf(dlog_file, "READ_EA ");
    if (access_mask & FILE_WRITE_DATA)
        fprintf(dlog_file, "WRITE ");
    if (access_mask & STANDARD_RIGHTS_WRITE)
        fprintf(dlog_file, "WRITE_ACL ");
    if (access_mask & FILE_WRITE_ATTRIBUTES)
        fprintf(dlog_file, "WRITE_ATTR ");
    if (access_mask & FILE_WRITE_EA)
        fprintf(dlog_file, "WRITE_EA ");
    if (access_mask & FILE_APPEND_DATA)
        fprintf(dlog_file, "APPEND ");
    if (access_mask & FILE_EXECUTE)
        fprintf(dlog_file, "EXECUTE ");
    if (access_mask & FILE_LIST_DIRECTORY)
        fprintf(dlog_file, "LIST ");
    if (access_mask & FILE_TRAVERSE)
        fprintf(dlog_file, "TRAVERSE ");
    if (access_mask & SYNCHRONIZE)
        fprintf(dlog_file, "SYNC ");
    if (access_mask & FILE_DELETE_CHILD)
        fprintf(dlog_file, "DELETE_CHILD");
    fprintf(dlog_file, "\n");
}