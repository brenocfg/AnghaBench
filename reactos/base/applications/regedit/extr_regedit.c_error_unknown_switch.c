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
typedef  int WCHAR ;
typedef  int* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 char* getAppName () ; 
 scalar_t__ iswalpha (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void error_unknown_switch(WCHAR chu, LPWSTR s)
{
    if (iswalpha(chu))
    {
        fwprintf(stderr, L"%s: Undefined switch /%c!\n", getAppName(), chu);
    }
    else
    {
        fwprintf(stderr, L"%s: Alphabetic character is expected after '%c' "
                          L"in switch specification\n", getAppName(), *(s - 1));
    }
    exit(1);
}