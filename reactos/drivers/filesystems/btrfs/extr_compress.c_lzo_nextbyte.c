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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t inpos; size_t inlen; int error; int /*<<< orphan*/ * in; } ;
typedef  TYPE_1__ lzo_stream ;

/* Variables and functions */

__attribute__((used)) static uint8_t lzo_nextbyte(lzo_stream* stream) {
    uint8_t c;

    if (stream->inpos >= stream->inlen) {
        stream->error = true;
        return 0;
    }

    c = stream->in[stream->inpos];
    stream->inpos++;

    return c;
}