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
typedef  scalar_t__ LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ PathIsURLW (scalar_t__) ; 
 scalar_t__ wcsstr (scalar_t__,char*) ; 

BOOL IsInternetLocation(LPCWSTR pszLocation)
{
    return (PathIsURLW(pszLocation) || wcsstr(pszLocation, L"www.") == pszLocation);
}