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
typedef  int /*<<< orphan*/  ut8 ;
struct des_state {int i; void* buflo; void* bufhi; int /*<<< orphan*/ * keyhi; int /*<<< orphan*/ * keylo; } ;

/* Variables and functions */
 void* be32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_des_permute_block0 (void**,void**) ; 
 int /*<<< orphan*/  r_des_permute_block1 (void**,void**) ; 
 int /*<<< orphan*/  r_des_round (void**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbe32 (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int des_encrypt (struct des_state *st, const ut8 *input, ut8 *output) {
	if (!st || !input || !output) {
		return false;
	}
	st->buflo = be32 (input + 0);
	st->bufhi = be32 (input + 4);

	//first permutation
	r_des_permute_block0 (&st->buflo, &st->bufhi);

 	for (st->i = 0; st->i < 16; st->i++) {
	   r_des_round (&st->buflo, &st->bufhi, &st->keylo[st->i], &st->keyhi[st->i]);
	}
 	//last permutation
	r_des_permute_block1 (&st->bufhi, &st->buflo);

	//result
	wbe32 (output + 0, st->bufhi);
	wbe32 (output + 4, st->buflo);

	return true;
}