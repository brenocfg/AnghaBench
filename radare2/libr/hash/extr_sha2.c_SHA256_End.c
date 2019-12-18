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
typedef  int ut8 ;
typedef  int R_SHA256_CTX ;

/* Variables and functions */
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (int*,int*) ; 
 int /*<<< orphan*/  r_mem_memzero (int*,int) ; 
 void** sha2_hex_digits ; 

char *SHA256_End(R_SHA256_CTX *context, char buffer[]) {
	ut8 digest[SHA256_DIGEST_LENGTH], *d = digest;
	int i;

	if (!context) {
		return NULL;
	}

	if (buffer) {
		SHA256_Final (digest, context);
		for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
			*buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
			*buffer++ = sha2_hex_digits[*d & 0x0f];
			d++;
		}
		*buffer = (char) 0;
	} else {
		r_mem_memzero (context, sizeof(*context));
	}
	r_mem_memzero (digest, SHA256_DIGEST_LENGTH);
	return buffer;
}