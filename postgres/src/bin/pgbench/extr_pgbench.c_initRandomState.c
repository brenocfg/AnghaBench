#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  xseed; } ;
struct TYPE_4__ {unsigned short* xseed; } ;
typedef  TYPE_1__ RandomState ;

/* Variables and functions */
 TYPE_3__ base_random_sequence ; 
 int pg_jrand48 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
initRandomState(RandomState *random_state)
{
	random_state->xseed[0] = (unsigned short)
		(pg_jrand48(base_random_sequence.xseed) & 0xFFFF);
	random_state->xseed[1] = (unsigned short)
		(pg_jrand48(base_random_sequence.xseed) & 0xFFFF);
	random_state->xseed[2] = (unsigned short)
		(pg_jrand48(base_random_sequence.xseed) & 0xFFFF);
}