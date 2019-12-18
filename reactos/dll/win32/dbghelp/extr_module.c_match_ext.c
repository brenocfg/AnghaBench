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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/ ** ext ; 
 size_t strlenW (int /*<<< orphan*/  const* const) ; 
 scalar_t__ strncmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const,size_t) ; 

__attribute__((used)) static int match_ext(const WCHAR* ptr, size_t len)
{
    const WCHAR* const *e;
    size_t      l;

    for (e = ext; *e; e++)
    {
        l = strlenW(*e);
        if (l >= len) return 0;
        if (strncmpiW(&ptr[len - l], *e, l)) continue;
        return l;
    }
    return 0;
}