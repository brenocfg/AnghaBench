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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  hInstance; } ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_STRING_LEN ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wcslen (char*) ; 

__attribute__((used)) static
VOID
DIALOG_AddFilterItem(LPWSTR* p, UINT ids, LPCWSTR filter)
{
    LoadStringW(Globals.hInstance, ids, *p, MAX_STRING_LEN);
    *p += wcslen(*p) + 1;
    lstrcpyW(*p, filter);
    *p += wcslen(*p) + 1;
    **p = '\0';
}