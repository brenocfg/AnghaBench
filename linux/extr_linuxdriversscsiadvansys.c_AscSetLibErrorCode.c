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
typedef  int ushort ;
struct TYPE_3__ {scalar_t__ err_code; int /*<<< orphan*/  iop_base; } ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_ASCDVC_ERR_CODE_W ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int AscSetLibErrorCode(ASC_DVC_VAR *asc_dvc, ushort err_code)
{
	if (asc_dvc->err_code == 0) {
		asc_dvc->err_code = err_code;
		AscWriteLramWord(asc_dvc->iop_base, ASCV_ASCDVC_ERR_CODE_W,
				 err_code);
	}
	return err_code;
}