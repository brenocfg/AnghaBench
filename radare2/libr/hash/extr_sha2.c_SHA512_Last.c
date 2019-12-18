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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
struct TYPE_4__ {int* bitcount; int* buffer; } ;
typedef  TYPE_1__ R_SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  REVERSE64 (int,int) ; 
 int SHA512_BLOCK_LENGTH ; 
 unsigned int SHA512_SHORT_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA512_Transform (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 

void SHA512_Last(R_SHA512_CTX *context) {
	unsigned int usedspace;

	usedspace = (context->bitcount[0] >> 3) % SHA512_BLOCK_LENGTH;
#if BYTE_ORDER == LITTLE_ENDIAN
	/* Convert FROM host byte order */
	REVERSE64 (context->bitcount[0], context->bitcount[0]);
	REVERSE64 (context->bitcount[1], context->bitcount[1]);
#endif
	if (usedspace > 0) {
		/* Begin padding with a 1 bit: */
		context->buffer[usedspace++] = 0x80;

		if (usedspace <= SHA512_SHORT_BLOCK_LENGTH) {
			/* Set-up for the last transform: */
			memset (&context->buffer[usedspace], 0, SHA512_SHORT_BLOCK_LENGTH - usedspace);
		} else {
			if (usedspace < SHA512_BLOCK_LENGTH) {
				memset (&context->buffer[usedspace], 0, SHA512_BLOCK_LENGTH - usedspace);
			}
			/* Do second-to-last transform: */
			SHA512_Transform (context, (ut64 *) context->buffer);

			/* And set-up for the last transform: */
			memset (context->buffer, 0, SHA512_BLOCK_LENGTH - 2);
		}
	} else {
		/* Prepare for final transform: */
		memset (context->buffer, 0, SHA512_SHORT_BLOCK_LENGTH);

		/* Begin padding with a 1 bit: */
		*context->buffer = 0x80;
	}
	/* Store the length of input data (in bits): */
#if WEAK_ALIASING
	*(ut64 *) &context->buffer[SHA512_SHORT_BLOCK_LENGTH] = context->bitcount[1];
	*(ut64 *) &context->buffer[SHA512_SHORT_BLOCK_LENGTH + 8] = context->bitcount[0];
#else
	{
		ut64 *p = (ut64 *) ((ut8 *) context->buffer + SHA512_SHORT_BLOCK_LENGTH);
		*p = (ut64) context->bitcount[1];
		p = (ut64 *) ((ut8 *) context->buffer + SHA512_SHORT_BLOCK_LENGTH + 8);
		*p = (ut64) context->bitcount[0];
	}
#endif

	/* Final transform: */
	SHA512_Transform (context, (ut64 *) context->buffer);
}