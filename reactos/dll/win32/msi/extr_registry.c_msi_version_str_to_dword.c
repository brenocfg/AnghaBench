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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoiW (scalar_t__) ; 
 scalar_t__ strchrW (scalar_t__,char) ; 

DWORD msi_version_str_to_dword(LPCWSTR p)
{
    DWORD major, minor = 0, build = 0, version = 0;

    if (!p)
        return version;

    major = atoiW(p);

    p = strchrW(p, '.');
    if (p)
    {
        minor = atoiW(p+1);
        p = strchrW(p+1, '.');
        if (p)
            build = atoiW(p+1);
    }

    return MAKELONG(build, MAKEWORD(minor, major));
}