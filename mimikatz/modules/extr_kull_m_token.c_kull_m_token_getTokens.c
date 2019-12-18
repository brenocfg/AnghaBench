#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mustContinue; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PKULL_M_TOKEN_ENUM_CALLBACK ;
typedef  TYPE_1__ KULL_M_TOKEN_ENUM_DATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int TOKEN_DUPLICATE ; 
 int TOKEN_QUERY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kull_m_handle_getHandlesOfType (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_process_getProcessInformation (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_token_getTokens_handles_callback ; 
 int /*<<< orphan*/  kull_m_token_getTokens_process_callback ; 

BOOL kull_m_token_getTokens(PKULL_M_TOKEN_ENUM_CALLBACK callBack, PVOID pvArg)
{
	BOOL status = FALSE;
	KULL_M_TOKEN_ENUM_DATA data = {callBack, pvArg, TRUE};
	if(status = NT_SUCCESS(kull_m_process_getProcessInformation(kull_m_token_getTokens_process_callback, &data)))
		if(data.mustContinue)
			status = NT_SUCCESS(kull_m_handle_getHandlesOfType(kull_m_token_getTokens_handles_callback, L"Token", TOKEN_QUERY | TOKEN_DUPLICATE, 0, &data));
	return status;
}