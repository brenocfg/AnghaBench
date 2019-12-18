#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* detail_no; void* error_no; } ;
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  void* HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Error ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_SetError  (HPDF_Error   error,
                HPDF_STATUS  error_no,
                HPDF_STATUS  detail_no)
{
    HPDF_PTRACE((" HPDF_SetError: error_no=0x%04X "
            "detail_no=0x%04X\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no));

    error->error_no = error_no;
    error->detail_no = detail_no;

    return error_no;
}