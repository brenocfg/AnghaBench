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
typedef  int ut8 ;
struct TYPE_4__ {scalar_t__ dir; } ;
typedef  TYPE_1__ RCrypto ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_decrypt (int /*<<< orphan*/ *,int* const,int* const) ; 
 int /*<<< orphan*/  aes_encrypt (int /*<<< orphan*/ *,int* const,int* const) ; 
 int* calloc (int,int const) ; 
 int /*<<< orphan*/  free (int* const) ; 
 int /*<<< orphan*/  memcpy (int* const,int const*,int) ; 
 int /*<<< orphan*/  memset (int* const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  r_crypto_append (TYPE_1__*,int* const,int const) ; 
 int /*<<< orphan*/  st ; 

__attribute__((used)) static bool update (RCrypto *cry, const ut8 *buf, int len) {
	// Pad to the block size, do not append dummy block
	const int diff = (BLOCK_SIZE - (len % BLOCK_SIZE)) % BLOCK_SIZE;
	const int size = len + diff;
	const int blocks = size / BLOCK_SIZE;
	int i;

	ut8 *const obuf = calloc (1, size);
	if (!obuf) {
		return false;
	}
	ut8 *const ibuf = calloc (1, size);
	if (!ibuf) {
		free (obuf);
		return false;
	}

	memset (ibuf, 0, size);
	memcpy (ibuf, buf, len);
	// Padding should start like 100000...
	if (diff) {
		ibuf[len] = 8; //0b1000;
	}

	if (cry->dir == 0) {
		for (i = 0; i < blocks; i++) {
			const int delta = BLOCK_SIZE * i;
			aes_encrypt (&st, ibuf + delta, obuf + delta);
		}
	} else if (cry->dir > 0) {
		for (i = 0; i < blocks; i++) {
			const int delta = BLOCK_SIZE * i;
			aes_decrypt (&st, ibuf + delta, obuf + delta);
		}
	}

	// printf("%128s\n", obuf);

	r_crypto_append (cry, obuf, size);
	free (obuf);
	free (ibuf);
	return true;
}