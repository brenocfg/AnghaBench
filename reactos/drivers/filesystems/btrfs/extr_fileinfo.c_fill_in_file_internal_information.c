#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  inode; int /*<<< orphan*/  subvol; } ;
typedef  TYPE_2__ fcb ;
struct TYPE_6__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_8__ {TYPE_1__ IndexNumber; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONG ;
typedef  TYPE_3__ FILE_INTERNAL_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  make_file_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS fill_in_file_internal_information(FILE_INTERNAL_INFORMATION* fii, fcb* fcb, LONG* length) {
    *length -= sizeof(FILE_INTERNAL_INFORMATION);

    fii->IndexNumber.QuadPart = make_file_id(fcb->subvol, fcb->inode);

    return STATUS_SUCCESS;
}