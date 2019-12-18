#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int passed; int length; int* buffer; int /*<<< orphan*/  state; int /*<<< orphan*/  passes; } ;
typedef  TYPE_1__ PHP_TIGER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tiger_compress (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void TigerFinalize(PHP_TIGER_CTX *context)
{
	context->passed += (uint64_t) context->length << 3;

	context->buffer[context->length++] = 0x1;
	if (context->length % 8) {
		memset(&context->buffer[context->length], 0, 8-context->length%8);
		context->length += 8-context->length%8;
	}

	if (context->length > 56) {
		memset(&context->buffer[context->length], 0, 64 - context->length);
		tiger_compress(context->passes, ((uint64_t *) context->buffer), context->state);
		memset(context->buffer, 0, 56);
	} else {
		memset(&context->buffer[context->length], 0, 56 - context->length);
	}

#ifndef WORDS_BIGENDIAN
	memcpy(&context->buffer[56], &context->passed, sizeof(uint64_t));
#else
	context->buffer[56] = (unsigned char) (context->passed & 0xff);
	context->buffer[57] = (unsigned char) ((context->passed >> 8) & 0xff);
	context->buffer[58] = (unsigned char) ((context->passed >> 16) & 0xff);
	context->buffer[59] = (unsigned char) ((context->passed >> 24) & 0xff);
	context->buffer[60] = (unsigned char) ((context->passed >> 32) & 0xff);
	context->buffer[61] = (unsigned char) ((context->passed >> 40) & 0xff);
	context->buffer[62] = (unsigned char) ((context->passed >> 48) & 0xff);
	context->buffer[63] = (unsigned char) ((context->passed >> 56) & 0xff);
#endif
	tiger_compress(context->passes, ((uint64_t *) context->buffer), context->state);
}