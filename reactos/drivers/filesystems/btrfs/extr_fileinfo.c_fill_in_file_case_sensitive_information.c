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
struct TYPE_5__ {scalar_t__ case_sensitive; } ;
typedef  TYPE_1__ fcb ;
struct TYPE_6__ {int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONG ;
typedef  TYPE_2__ FILE_CASE_SENSITIVE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_CS_FLAG_CASE_SENSITIVE_DIR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS fill_in_file_case_sensitive_information(FILE_CASE_SENSITIVE_INFORMATION* fcsi, fcb* fcb, LONG* length) {
    fcsi->Flags = fcb->case_sensitive ? FILE_CS_FLAG_CASE_SENSITIVE_DIR : 0;

    *length -= sizeof(FILE_CASE_SENSITIVE_INFORMATION);

    return STATUS_SUCCESS;
}