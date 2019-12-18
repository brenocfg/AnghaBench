#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  CurrentByteOffset; } ;
struct TYPE_6__ {int /*<<< orphan*/  CurrentByteOffset; } ;
typedef  TYPE_1__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONG ;
typedef  TYPE_2__ FILE_POSITION_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS fill_in_file_position_information(FILE_POSITION_INFORMATION* fpi, PFILE_OBJECT FileObject, LONG* length) {
    RtlZeroMemory(fpi, sizeof(FILE_POSITION_INFORMATION));

    *length -= sizeof(FILE_POSITION_INFORMATION);

    fpi->CurrentByteOffset = FileObject->CurrentByteOffset;

    return STATUS_SUCCESS;
}