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
 int /*<<< orphan*/  KeccakP1600_Permute_Nrounds (void*,int) ; 

void KeccakP1600_Permute_12rounds(void *state)
{
     KeccakP1600_Permute_Nrounds(state, 12);
}