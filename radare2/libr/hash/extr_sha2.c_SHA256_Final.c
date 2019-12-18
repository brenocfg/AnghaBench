#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_5__ {int bitcount; int* buffer; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ R_SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  REVERSE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVERSE64 (int,int) ; 
 int SHA256_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA256_DIGEST_LENGTH ; 
 unsigned int SHA256_SHORT_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA256_Transform (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  r_mem_memzero (TYPE_1__*,int) ; 

void SHA256_Final(ut8 *digest, R_SHA256_CTX *context) {
	ut32 *d = (ut32 *) digest;
	unsigned int usedspace;

	/* Sanity check: */
	if (!context) {
		return;
	}

	/* If no digest buffer is passed, we don't bother doing this: */
	if (digest != (ut8 *) 0) {
		usedspace = (context->bitcount >> 3) % SHA256_BLOCK_LENGTH;
#if BYTE_ORDER == LITTLE_ENDIAN
		/* Convert FROM host byte order */
		REVERSE64 (context->bitcount, context->bitcount);
#endif
		if (usedspace > 0) {
			/* Begin padding with a 1 bit: */
			context->buffer[usedspace++] = 0x80;

			if (usedspace <= SHA256_SHORT_BLOCK_LENGTH) {
				/* Set-up for the last transform: */
				memset (&context->buffer[usedspace], 0, SHA256_SHORT_BLOCK_LENGTH - usedspace);
			} else {
				if (usedspace < SHA256_BLOCK_LENGTH) {
					memset (&context->buffer[usedspace], 0, SHA256_BLOCK_LENGTH - usedspace);
				}
				/* Do second-to-last transform: */
				SHA256_Transform (context, (ut32 *) context->buffer);

				/* And set-up for the last transform: */
				memset (context->buffer, 0, SHA256_SHORT_BLOCK_LENGTH);
			}
		} else {
			/* Set-up for the last transform: */
			memset (context->buffer, 0, SHA256_SHORT_BLOCK_LENGTH);

			/* Begin padding with a 1 bit: */
			*context->buffer = 0x80;
		}
		/* Set the bit count: */
#if WEAK_ALIASING
		*(ut64 *) &context->buffer[SHA256_SHORT_BLOCK_LENGTH] = context->bitcount;
#else
		{
			ut64 *p = (ut64 *) ((ut8 *) context->buffer + SHA256_SHORT_BLOCK_LENGTH);
			*p = (ut64) context->bitcount;
		}
#endif

		/* Final transform: */
		SHA256_Transform (context, (ut32 *) context->buffer);

#if BYTE_ORDER == LITTLE_ENDIAN
		{
			/* Convert TO host byte order */
			int j;
			for (j = 0; j < 8; j++) {
				REVERSE32 (context->state[j], context->state[j]);
				*d++ = context->state[j];
			}
		}
#else
		memcpy (d, context->state, SHA256_DIGEST_LENGTH);
#endif
	}

	/* Clean up state data: */
	r_mem_memzero (context, sizeof(*context));
	usedspace = 0;
}