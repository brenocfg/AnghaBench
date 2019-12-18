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
typedef  int /*<<< orphan*/  enabled ;

/* Variables and functions */
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int 
cpu_supports_avx() 
{
    int enabled, r;
    size_t length = sizeof(enabled);
    r = sysctlbyname("hw.optional.avx1_0", &enabled, &length, NULL, 0);
    if ( r == 0 && enabled != 0) {
        return 1;
    }
    else {
        return 0;
    }
}