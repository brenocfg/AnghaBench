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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ pcg_state_setseq_128 ;

/* Variables and functions */
 int /*<<< orphan*/  pcg_output_xsl_rr_128_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcg_setseq_128_step_r (TYPE_1__*) ; 

__attribute__((used)) static inline uint64_t
pcg_setseq_128_xsl_rr_64_random_r(pcg_state_setseq_128* rng)
{
    pcg_setseq_128_step_r(rng);
    return pcg_output_xsl_rr_128_64(rng->state);
}