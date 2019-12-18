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

/* Variables and functions */
 int /*<<< orphan*/  is_sep (char const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline const char* file_name(const char* str)
{
    const char*       p;

    for (p = str + strlen(str) - 1; p >= str && !is_sep(*p); p--);
    return p + 1;
}