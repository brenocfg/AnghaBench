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
struct xor_state {int key_size; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool xor_init(struct xor_state *const state, const ut8 *key, int keylen) {
	if (!state || !key || keylen < 1) { // || keylen > MAX_xor_KEY_SIZE) {
		return false;
	}
	state->key_size = keylen;
	state->key = malloc (keylen);
	memcpy (state->key, key, keylen);
	return true;
}