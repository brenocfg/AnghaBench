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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  ranctx ;

/* Variables and functions */
 unsigned long ranval (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void full_shuffle(tree *newtree, unsigned long length, ranctx *prng_state)
{
	unsigned long i, randnum;

	for (i = length - 1; i > 0; i--) {
		tree tmp;
		randnum = ranval(prng_state) % (i + 1);
		tmp = newtree[i];
		newtree[i] = newtree[randnum];
		newtree[randnum] = tmp;
	}
}