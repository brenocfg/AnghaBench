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
typedef  size_t PCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  _wcsnicmp (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  wcsicmp (size_t,size_t) ; 
 size_t wcslen (size_t) ; 

BOOL SdbpMatchLayer(PCWSTR start, PCWSTR end, PCWSTR compare)
{
    size_t len;
    if (!end)
        return !wcsicmp(start, compare);
    len = end - start;
    return wcslen(compare) == len && !_wcsnicmp(start, compare, len);
}