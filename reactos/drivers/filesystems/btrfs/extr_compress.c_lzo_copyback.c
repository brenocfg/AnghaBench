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
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t outpos; int error; int outlen; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ lzo_stream ;

/* Variables and functions */

__attribute__((used)) static void lzo_copyback(lzo_stream* stream, uint32_t back, int len) {
    if (stream->outpos < back) {
        stream->error = true;
        return;
    }

    if (stream->outpos + len > stream->outlen) {
        stream->error = true;
        return;
    }

    do {
        stream->out[stream->outpos] = stream->out[stream->outpos - back];
        stream->outpos++;
        len--;
    } while (len > 0);
}