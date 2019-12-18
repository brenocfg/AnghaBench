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
typedef  int u32 ;
struct TYPE_2__ {int start; int last; } ;

/* Variables and functions */
 int max_endpoint ; 
 int nnodes ; 
 TYPE_1__* nodes ; 
 int nsearches ; 
 int prandom_u32_state (int /*<<< orphan*/ *) ; 
 int* queries ; 
 int /*<<< orphan*/  rnd ; 

__attribute__((used)) static void init(void)
{
	int i;

	for (i = 0; i < nnodes; i++) {
		u32 b = (prandom_u32_state(&rnd) >> 4) % max_endpoint;
		u32 a = (prandom_u32_state(&rnd) >> 4) % b;

		nodes[i].start = a;
		nodes[i].last = b;
	}

	/*
	 * Limit the search scope to what the user defined.
	 * Otherwise we are merely measuring empty walks,
	 * which is pointless.
	 */
	for (i = 0; i < nsearches; i++)
		queries[i] = (prandom_u32_state(&rnd) >> 4) % max_endpoint;
}