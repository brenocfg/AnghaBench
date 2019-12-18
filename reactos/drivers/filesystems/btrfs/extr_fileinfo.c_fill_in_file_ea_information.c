#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ealen; } ;
typedef  TYPE_1__ fcb ;
struct TYPE_6__ {int /*<<< orphan*/  EaSize; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONG ;
typedef  TYPE_2__ FILE_EA_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS fill_in_file_ea_information(FILE_EA_INFORMATION* eai, fcb* fcb, LONG* length) {
    *length -= sizeof(FILE_EA_INFORMATION);

    /* This value appears to be the size of the structure NTFS stores on disk, and not,
     * as might be expected, the size of FILE_FULL_EA_INFORMATION (which is what we store).
     * The formula is 4 bytes as a header, followed by 5 + NameLength + ValueLength for each
     * item. */

    eai->EaSize = fcb->ealen;

    return STATUS_SUCCESS;
}