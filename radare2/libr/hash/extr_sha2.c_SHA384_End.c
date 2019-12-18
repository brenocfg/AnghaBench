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
typedef  int R_SHA384_CTX ;

/* Variables and functions */
 int SHA384_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA384_Final (int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 void** sha2_hex_digits ; 

char *SHA384_End(R_SHA384_CTX *context, char buffer[]) {
	ut8 digest[SHA384_DIGEST_LENGTH], *d = digest;
	int i;

	/* Sanity check: */
	if (!context) {
		return NULL;
	}

	if (buffer != (char *) 0) {
		SHA384_Final (digest, context);

		for (i = 0; i < SHA384_DIGEST_LENGTH; i++) {
			*buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
			*buffer++ = sha2_hex_digits[*d & 0x0f];
			d++;
		}
		*buffer = (char) 0;
	} else {
		memset (context, 0, sizeof(*context));
	}
	memset (digest, 0, SHA384_DIGEST_LENGTH);
	return buffer;
}