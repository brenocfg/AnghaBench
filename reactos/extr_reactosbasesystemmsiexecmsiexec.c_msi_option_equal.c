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
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  msi_strequal (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL msi_option_equal(LPCWSTR str1, LPCSTR str2)
{
    if (str1[0] != '/' && str1[0] != '-')
        return FALSE;

    /* skip over the hyphen or slash */
    return msi_strequal(str1 + 1, str2);
}