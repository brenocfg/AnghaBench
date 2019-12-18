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
typedef  unsigned long long ut64 ;

/* Variables and functions */
 unsigned long long R_HASH_NBITS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* r_crypto_name (unsigned long long) ; 
 char* r_hash_name (unsigned long long) ; 

__attribute__((used)) static void algolist() {
	ut64 bits;
	ut64 i;
	for (i = 0; i < R_HASH_NBITS; i++) {
		bits = 1ULL << i;
		const char *name = r_hash_name (bits);
		if (name && *name) {
			printf ("h  %s\n", name);
		}
	}
	// TODO: do not hardcode
	printf ("e  base64\n");
	printf ("e  base91\n");
	printf ("e  punycode\n");
	for (i = 0;; i++) {
		bits = ((ut64) 1) << i;
		const char *name = r_crypto_name (bits);
		if (!name || !*name) {
			break;
		}
		printf ("c  %s\n", name);
	}
}