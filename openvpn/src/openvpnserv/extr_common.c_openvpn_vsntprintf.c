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
typedef  int /*<<< orphan*/  va_list ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int _vsntprintf (scalar_t__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
openvpn_vsntprintf(LPTSTR str, size_t size, LPCTSTR format, va_list arglist)
{
    int len = -1;
    if (size > 0)
    {
        len = _vsntprintf(str, size, format, arglist);
        str[size - 1] = 0;
    }
    return (len >= 0 && (size_t)len < size);
}