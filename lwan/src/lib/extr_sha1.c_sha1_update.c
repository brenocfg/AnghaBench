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
struct TYPE_3__ {size_t* count; unsigned char const* buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sha1_transform (int /*<<< orphan*/ ,unsigned char const*) ; 

void sha1_update(sha1_context *context, const unsigned char *data, size_t len)
{
    size_t i;
    size_t j;

    j = context->count[0];
    if ((context->count[0] += len << 3) < j)
        context->count[1]++;
    context->count[1] += (len >> 29);

    j = (j >> 3) & 63;

    if ((j + len) > 63) {
        i = 64 - j;
        memcpy(&context->buffer[j], data, i);
        sha1_transform(context->state, context->buffer);

        for (; i + 63 < len; i += 64)
            sha1_transform(context->state, &data[i]);

        j = 0;
    } else {
        i = 0;
    }

    memcpy(&context->buffer[j], &data[i], len - i);
}