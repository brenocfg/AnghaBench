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
 int /*<<< orphan*/  is_sepW (int /*<<< orphan*/  const) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline const WCHAR* file_nameW(const WCHAR* str)
{
    const WCHAR*      p;

    for (p = str + strlenW(str) - 1; p >= str && !is_sepW(*p); p--);
    return p + 1;
}