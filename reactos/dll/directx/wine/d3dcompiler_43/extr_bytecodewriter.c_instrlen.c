#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ rel_reg; } ;
struct instruction {TYPE_2__* src; TYPE_1__ dst; scalar_t__ has_predicate; } ;
struct TYPE_4__ {scalar_t__ rel_reg; } ;
typedef  unsigned int DWORD ;

/* Variables and functions */

__attribute__((used)) static DWORD instrlen(const struct instruction *instr, unsigned int srcs, unsigned int dsts) {
    unsigned int i;
    DWORD ret = srcs + dsts + (instr->has_predicate ? 1 : 0);

    if(dsts){
        if(instr->dst.rel_reg) ret++;
    }
    for(i = 0; i < srcs; i++) {
        if(instr->src[i].rel_reg) ret++;
    }
    return ret;
}