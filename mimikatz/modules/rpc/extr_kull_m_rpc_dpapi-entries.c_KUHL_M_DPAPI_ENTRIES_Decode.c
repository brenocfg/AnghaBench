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
typedef  int /*<<< orphan*/  KUHL_M_DPAPI_ENTRIES ;

/* Variables and functions */
 int /*<<< orphan*/  DPAPIEntries_StubDesc ; 
 int /*<<< orphan*/  NdrMesTypeDecode2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __MIDL_TypePicklingInfo ; 
 size_t _dpapi2Dentries_MIDL_TYPE_FORMAT_OFFSET ; 
 TYPE_1__ dpapi2Dentries__MIDL_TypeFormatString ; 

void KUHL_M_DPAPI_ENTRIES_Decode(handle_t _MidlEsHandle, KUHL_M_DPAPI_ENTRIES * _pType)
{
    NdrMesTypeDecode2(_MidlEsHandle, (PMIDL_TYPE_PICKLING_INFO) &__MIDL_TypePicklingInfo, &DPAPIEntries_StubDesc, (PFORMAT_STRING) &dpapi2Dentries__MIDL_TypeFormatString.Format[_dpapi2Dentries_MIDL_TYPE_FORMAT_OFFSET], _pType);
}