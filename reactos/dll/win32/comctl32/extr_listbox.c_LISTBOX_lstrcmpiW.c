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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LCID ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CSTR_GREATER_THAN ; 
 scalar_t__ CSTR_LESS_THAN ; 
 scalar_t__ CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 

__attribute__((used)) static inline INT LISTBOX_lstrcmpiW( LCID lcid, LPCWSTR str1, LPCWSTR str2 )
{
    INT ret = CompareStringW( lcid, NORM_IGNORECASE, str1, -1, str2, -1 );
    if (ret == CSTR_LESS_THAN)
        return -1;
    if (ret == CSTR_EQUAL)
        return 0;
    if (ret == CSTR_GREATER_THAN)
        return 1;
    return -1;
}