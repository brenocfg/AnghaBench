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
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL mongolian_wordbreak(WCHAR chr)
{
    return ((chr == 0x0020) || (chr == 0x200C) || (chr == 0x202F) || (chr == 0x180E) || (chr == 0x1800) || (chr == 0x1802) || (chr == 0x1803) || (chr == 0x1805) || (chr == 0x1808) || (chr == 0x1809) || (chr == 0x1807));
}