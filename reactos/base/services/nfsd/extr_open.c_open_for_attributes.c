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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FILE_APPEND_DATA ; 
 scalar_t__ FILE_CREATE ; 
 scalar_t__ FILE_EXECUTE ; 
 scalar_t__ FILE_OPEN ; 
 scalar_t__ FILE_OPEN_IF ; 
 scalar_t__ FILE_OVERWRITE ; 
 scalar_t__ FILE_OVERWRITE_IF ; 
 scalar_t__ FILE_READ_DATA ; 
 scalar_t__ FILE_SUPERSEDE ; 
 scalar_t__ FILE_WRITE_DATA ; 
 scalar_t__ NF4DIR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (int,char*) ; 

__attribute__((used)) static BOOLEAN open_for_attributes(uint32_t type, ULONG access_mask, 
                                   ULONG disposition, int status)
{
    if (type == NF4DIR) {
        if (disposition == FILE_OPEN || disposition == FILE_OVERWRITE ||
                (!status && (disposition == FILE_OPEN_IF || 
                    disposition == FILE_OVERWRITE_IF || 
                    disposition == FILE_SUPERSEDE))) {
            dprintf(1, "Opening a directory\n");
            return TRUE;
        } else {
            dprintf(1, "Creating a directory\n");
            return FALSE;
        }
    }

    if ((access_mask & FILE_READ_DATA) ||
            (access_mask & FILE_WRITE_DATA) ||
            (access_mask & FILE_APPEND_DATA) ||
            (access_mask & FILE_EXECUTE) ||
            disposition == FILE_CREATE ||
            disposition == FILE_OVERWRITE_IF ||
            disposition == FILE_SUPERSEDE ||
            disposition == FILE_OPEN_IF ||
            disposition == FILE_OVERWRITE)
        return FALSE;
    else {
        dprintf(1, "Open call that wants to manage attributes\n");
        return TRUE;
    }
}