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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ R_SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  REVERSE64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA512_Last (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_mem_memzero (TYPE_1__*,int) ; 

void SHA512_Final(ut8 digest[], R_SHA512_CTX *context) {
	ut64 *d = (ut64 *) digest;

	/* Sanity check: */
	if (!context) {
		return;
	}

	/* If no digest buffer is passed, we don't bother doing this: */
	if (digest != (ut8 *) 0) {
		SHA512_Last (context);

		/* Save the hash data for output: */
#if BYTE_ORDER == LITTLE_ENDIAN
		{
			/* Convert TO host byte order */
			int j;
			for (j = 0; j < 8; j++) {
				REVERSE64 (context->state[j], context->state[j]);
				*d++ = context->state[j];
			}
		}
#else
		memcpy (d, context->state, SHA512_DIGEST_LENGTH);
#endif
	}

	/* Zero out state data */
	r_mem_memzero (context, sizeof(*context));
}