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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int* bitcount; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ R_SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ADDINC128 (int*,size_t) ; 
 int SHA512_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA512_Transform (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void SHA512_Update(R_SHA512_CTX *context, const ut8 *data, size_t len) {
	unsigned int freespace, usedspace;

	if (len == 0) {
		/* Calling with no data is valid - we do nothing */
		return;
	}

	/* Sanity check: */
	if (!context || !data) {
		return;
	}

	usedspace = (context->bitcount[0] >> 3) % SHA512_BLOCK_LENGTH;
	if (usedspace > 0) {
		/* Calculate how much free space is available in the buffer */
		freespace = SHA512_BLOCK_LENGTH - usedspace;

		if (len >= freespace) {
			/* Fill the buffer completely and process it */
			memcpy (&context->buffer[usedspace], data, freespace);
			ADDINC128 (context->bitcount, freespace << 3);
			len -= freespace;
			data += freespace;
			SHA512_Transform (context, (ut64 *) context->buffer);
		} else {
			/* The buffer is not yet full */
			memcpy (&context->buffer[usedspace], data, len);
			ADDINC128 (context->bitcount, len << 3);
			/* Clean up: */
			usedspace = freespace = 0;
			return;
		}
	}
	while (len >= SHA512_BLOCK_LENGTH) {
		/* Process as many complete blocks as we can */
		SHA512_Transform (context, (ut64 *) data);
		ADDINC128 (context->bitcount, SHA512_BLOCK_LENGTH << 3);
		len -= SHA512_BLOCK_LENGTH;
		data += SHA512_BLOCK_LENGTH;
	}
	if (len > 0) {
		/* There's left-overs, so save 'em */
		memcpy (context->buffer, data, len);
		ADDINC128 (context->bitcount, len << 3);
	}
	/* Clean up: */
	usedspace = freespace = 0;
}