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
typedef  int /*<<< orphan*/  sha2_word64 ;
typedef  int /*<<< orphan*/  sha2_byte ;
struct TYPE_4__ {int /*<<< orphan*/ * state; } ;
typedef  int /*<<< orphan*/  SHA512_CTX ;
typedef  TYPE_1__ SHA384_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCPY_BCOPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMSET_BZERO (TYPE_1__*,int) ; 
 int /*<<< orphan*/  REVERSE64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA384_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA512_Last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void SHA384_Final(sha2_byte digest[], SHA384_CTX* context) {
	sha2_word64	*d = (sha2_word64*)digest;

	/* Sanity check: */
	assert(context != NULL);

	/* If no digest buffer is passed, we don't bother doing this: */
	if (digest != NULL) {
		SHA512_Last((SHA512_CTX*)context);

		/* Save the hash data for output: */
#ifndef WORDS_BIGENDIAN
		{
			/* Convert TO host byte order */
			int	j;
			for (j = 0; j < 6; j++) {
				REVERSE64(context->state[j],context->state[j]);
				*d++ = context->state[j];
			}
		}
#else
		MEMCPY_BCOPY(d, context->state, SHA384_DIGEST_LENGTH);
#endif
	}

	/* Zero out state data */
	MEMSET_BZERO(context, sizeof(*context));
}