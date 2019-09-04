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
struct rsc {int conj; int idx; } ;

/* Variables and functions */

__attribute__((used)) static int daio_master(struct rsc *rsc)
{
	/* Actually, this is not the resource index of DAIO.
	 * For DAO, it is the input mapper index. And, for DAI,
	 * it is the output time-slot index. */
	return rsc->conj = rsc->idx;
}