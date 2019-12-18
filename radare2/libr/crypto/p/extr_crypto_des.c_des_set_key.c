#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
struct TYPE_5__ {int key_size; int rounds; int /*<<< orphan*/ * keyhi; int /*<<< orphan*/ * keylo; } ;
struct TYPE_4__ {int dir; } ;
typedef  TYPE_1__ RCrypto ;

/* Variables and functions */
 int DES_KEY_SIZE ; 
 int be32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_des_permute_key (int*,int*) ; 
 int /*<<< orphan*/  r_des_round_key (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 TYPE_2__ st ; 

__attribute__((used)) static bool des_set_key (RCrypto *cry, const ut8 *key, int keylen, int mode, int direction) {
	ut32 keylo, keyhi, i;
	if (keylen != DES_KEY_SIZE) {
		return false;
	}
	// splitting the key in hi & lo
	keylo = be32 (key);
	keyhi = be32 (key + 4);

	st.key_size = DES_KEY_SIZE;
	st.rounds = 16;
	cry->dir = direction; // = direction == 0;
	// key permutation to derive round keys
	r_des_permute_key (&keylo, &keyhi);

	for (i = 0; i < 16; ++i) {
		// filling round keys space
		r_des_round_key (i, &st.keylo[i], &st.keyhi[i], &keylo, &keyhi);
	}

	return true;
}