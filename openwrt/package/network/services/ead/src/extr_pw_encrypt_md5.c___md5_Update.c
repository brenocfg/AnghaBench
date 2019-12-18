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
struct MD5Context {int* count; unsigned char const* buffer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __md5_Transform (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static void __md5_Update(struct MD5Context *context, const unsigned char *input, unsigned int inputLen)
{
	unsigned int i, idx, partLen;

	/* Compute number of bytes mod 64 */
	idx = (context->count[0] >> 3) & 0x3F;

	/* Update number of bits */
	context->count[0] += (inputLen << 3);
	if (context->count[0] < (inputLen << 3))
		context->count[1]++;
	context->count[1] += (inputLen >> 29);

	partLen = 64 - idx;

	/* Transform as many times as possible. */
	if (inputLen >= partLen) {
		memcpy(&context->buffer[idx], input, partLen);
		__md5_Transform(context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			__md5_Transform(context->state, &input[i]);

		idx = 0;
	} else
		i = 0;

	/* Buffer remaining input */
	memcpy(&context->buffer[idx], &input[i], inputLen - i);
}