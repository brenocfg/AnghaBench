#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* val; void* key; } ;

/* Variables and functions */
 int nnodes ; 
 TYPE_1__* nodes ; 
 void* prandom_u32_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rnd ; 

__attribute__((used)) static void init(void)
{
	int i;
	for (i = 0; i < nnodes; i++) {
		nodes[i].key = prandom_u32_state(&rnd);
		nodes[i].val = prandom_u32_state(&rnd);
	}
}