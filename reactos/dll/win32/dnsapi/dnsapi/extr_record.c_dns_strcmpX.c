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
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int lstrcmpiA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_strcmpX( LPCVOID str1, LPCVOID str2, BOOL wide )
{
    if (wide)
        return lstrcmpiW( str1, str2 );
    else
        return lstrcmpiA( str1, str2 );
}