#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/ * Format; } ;
typedef  int /*<<< orphan*/  PMIDL_TYPE_PICKLING_INFO ;
typedef  int /*<<< orphan*/  PKERB_VALIDATION_INFO ;
typedef  int /*<<< orphan*/  PFORMAT_STRING ;

/* Variables and functions */
 size_t NdrMesTypeAlignSize2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __MIDL_TypePicklingInfo ; 
 size_t _ms_pac_PKERB_VALIDATION_INFO_idx ; 
 int /*<<< orphan*/  msKrbPac_StubDesc ; 
 TYPE_1__ ms_pac__MIDL_TypeFormatString ; 

size_t PKERB_VALIDATION_INFO_AlignSize(handle_t _MidlEsHandle, PKERB_VALIDATION_INFO * _pType)
{
	return NdrMesTypeAlignSize2(_MidlEsHandle, (PMIDL_TYPE_PICKLING_INFO) &__MIDL_TypePicklingInfo, &msKrbPac_StubDesc, (PFORMAT_STRING) &ms_pac__MIDL_TypeFormatString.Format[_ms_pac_PKERB_VALIDATION_INFO_idx], _pType);
}