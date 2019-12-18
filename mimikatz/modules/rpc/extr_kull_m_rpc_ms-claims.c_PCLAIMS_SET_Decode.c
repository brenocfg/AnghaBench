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
typedef  int /*<<< orphan*/  PFORMAT_STRING ;
typedef  int /*<<< orphan*/  PCLAIMS_SET ;

/* Variables and functions */
 int /*<<< orphan*/  Claims_StubDesc ; 
 TYPE_1__ Claims__MIDL_TypeFormatString ; 
 int /*<<< orphan*/  NdrMesTypeDecode2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __MIDL_TypePicklingInfo ; 

void PCLAIMS_SET_Decode(handle_t _MidlEsHandle, PCLAIMS_SET * _pType)
{
    NdrMesTypeDecode2(_MidlEsHandle, (PMIDL_TYPE_PICKLING_INFO) &__MIDL_TypePicklingInfo, &Claims_StubDesc, (PFORMAT_STRING) &Claims__MIDL_TypeFormatString.Format[2], _pType);
}