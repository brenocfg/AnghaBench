#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {unsigned int cc_aloc; } ;
typedef  TYPE_1__ scc_t ;

/* Variables and functions */
 scalar_t__ realloc (TYPE_1__*,int) ; 

__attribute__((used)) static scc_t* scc_relloc(scc_t* scc, unsigned int cc_count)
{
    if (0 == scc || scc->cc_aloc < cc_count) {
        // alloc 1.5 time what is asked for.
        scc = (scc_t*)realloc(scc, sizeof(scc_t) + ((cc_count * 15 / 10) * sizeof(uint16_t)));
        scc->cc_aloc = cc_count;
    }

    return scc;
}