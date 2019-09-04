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
struct rol_state {int key_size; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int MAX_rol_KEY_SIZE ; 

__attribute__((used)) static bool rol_init(struct rol_state *const state, const ut8 *key, int keylen) {
	if (!state || !key || keylen < 1 || keylen > MAX_rol_KEY_SIZE) {
		return false;
	}
	int i;
	state->key_size = keylen;
	for (i = 0; i < keylen; i++) {
		state->key[i] = key[i];
	}
	return true;
}