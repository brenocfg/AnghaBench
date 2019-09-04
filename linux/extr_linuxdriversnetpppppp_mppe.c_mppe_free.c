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
struct ppp_mppe_state {int /*<<< orphan*/  arc4; TYPE_1__* sha1; struct ppp_mppe_state* sha1_digest; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ppp_mppe_state*) ; 
 int /*<<< orphan*/  kzfree (TYPE_1__*) ; 

__attribute__((used)) static void mppe_free(void *arg)
{
	struct ppp_mppe_state *state = (struct ppp_mppe_state *) arg;
	if (state) {
		kfree(state->sha1_digest);
		crypto_free_shash(state->sha1->tfm);
		kzfree(state->sha1);
		crypto_free_skcipher(state->arc4);
		kfree(state);
	}
}