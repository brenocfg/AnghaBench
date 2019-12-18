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
struct TYPE_4__ {struct TYPE_4__* next; scalar_t__ hToken; int /*<<< orphan*/  ptid; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ (* PKULL_M_TOKEN_ENUM_CALLBACK ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_1__ KULL_M_TOKEN_LIST ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ kull_m_token_getTokens (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_token_getTokensUnique_callback ; 

BOOL kull_m_token_getTokensUnique(PKULL_M_TOKEN_ENUM_CALLBACK callBack, PVOID pvArg)
{
	BOOL status = FALSE, mustContinue = TRUE;
	KULL_M_TOKEN_LIST list = {0}, *cur, *tmp;
	if(status = kull_m_token_getTokens(kull_m_token_getTokensUnique_callback, &list))
	{
		for(cur = &list; cur && mustContinue; cur = cur->next)
			mustContinue = callBack(cur->hToken, cur->ptid, pvArg);

		for(cur = &list; cur; cur = tmp)
		{
			if(cur->hToken)
				CloseHandle(cur->hToken);
			tmp = cur->next;
			if(cur != &list)
				LocalFree(cur);
		}
	}
	return status;
}