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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_5__ {int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ pg_sha224_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  PG_SHA224_DIGEST_LENGTH ; 
 int /*<<< orphan*/  REVERSE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA256_Last (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
pg_sha224_final(pg_sha224_ctx *context, uint8 *digest)
{
	/* If no digest buffer is passed, we don't bother doing this: */
	if (digest != NULL)
	{
		SHA256_Last(context);

#ifndef WORDS_BIGENDIAN
		{
			/* Convert TO host byte order */
			int			j;

			for (j = 0; j < 8; j++)
			{
				REVERSE32(context->state[j], context->state[j]);
			}
		}
#endif
		memcpy(digest, context->state, PG_SHA224_DIGEST_LENGTH);
	}

	/* Clean up state data: */
	memset(context, 0, sizeof(pg_sha224_ctx));
}