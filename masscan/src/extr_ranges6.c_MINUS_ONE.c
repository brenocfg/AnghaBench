#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long long lo; scalar_t__ hi; } ;
typedef  TYPE_1__ ipv6address ;

/* Variables and functions */

__attribute__((used)) static ipv6address
MINUS_ONE(const ipv6address ip)
{
    ipv6address result;
    
    if (ip.lo == 0) {
        result.hi = ip.hi - 1;
        result.lo = ~0ULL;
    } else {
        result.hi = ip.hi;
        result.lo = ip.lo - 1;
    }

    return result;
}