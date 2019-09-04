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
typedef  void* WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {void* wMinute; void* wHour; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetTimeFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  TIME_NOSECONDS ; 

__attribute__((used)) static
VOID
JobTimeToTimeString(
    PWSTR pszBuffer,
    INT cchBuffer,
    WORD wHour,
    WORD wMinute)
{
    SYSTEMTIME Time = {0, 0, 0, 0, 0, 0, 0, 0};

    Time.wHour = wHour;
    Time.wMinute = wMinute;

    GetTimeFormat(LOCALE_USER_DEFAULT,
                  TIME_NOSECONDS,
                  &Time,
                  NULL,
                  pszBuffer,
                  cchBuffer);
}