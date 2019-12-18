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
typedef  int /*<<< orphan*/  RCrypto ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ flag ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_crypto_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rc6_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc6_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st ; 

__attribute__((used)) static bool update(RCrypto *cry, const ut8 *buf, int len) {
	if (len % BLOCK_SIZE != 0) { //let user handle with with pad.
		eprintf ("Input should be multiple of 128bit.\n");
		return false;
	}

	const int blocks = len / BLOCK_SIZE;

	ut8 *obuf = calloc (1, len);
	if (!obuf) {
		return false;
	}

	int i;
	if (flag) {
		for (i = 0; i < blocks; i++) {
			rc6_decrypt (&st, buf + BLOCK_SIZE * i, obuf + BLOCK_SIZE * i);
		}
	} else {
		for (i = 0; i < blocks; i++) {
			rc6_encrypt (&st, buf + BLOCK_SIZE * i, obuf + BLOCK_SIZE * i);
		}
	}

	r_crypto_append (cry, obuf, len);
	free (obuf);
	return true;
}