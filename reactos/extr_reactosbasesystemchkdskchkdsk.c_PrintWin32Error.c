#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConMsgPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FORMAT_MESSAGE_FROM_SYSTEM ; 
 int /*<<< orphan*/  LANG_USER_DEFAULT ; 
 int /*<<< orphan*/  StdErr ; 

__attribute__((used)) static VOID PrintWin32Error(int Message, DWORD ErrorCode)
{
    ConResPuts(StdErr, Message);
    ConMsgPuts(StdErr, FORMAT_MESSAGE_FROM_SYSTEM,
               NULL, ErrorCode, LANG_USER_DEFAULT);
    ConPuts(StdErr, L"\n");
}