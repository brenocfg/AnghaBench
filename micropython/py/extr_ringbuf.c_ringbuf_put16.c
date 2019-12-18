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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int iput; int size; int iget; int* buf; } ;
typedef  TYPE_1__ ringbuf_t ;

/* Variables and functions */

int ringbuf_put16(ringbuf_t *r, uint16_t v) {
    uint32_t iput_a = r->iput + 1;
    if (iput_a == r->size) {
        iput_a = 0;
    }
    if (iput_a == r->iget) {
        return -1;
    }
    uint32_t iput_b = iput_a + 1;
    if (iput_b == r->size) {
        iput_b = 0;
    }
    if (iput_b == r->iget) {
        return -1;
    }
    r->buf[r->iput] = (v >> 8) & 0xff;
    r->buf[iput_a] = v & 0xff;
    r->iput = iput_b;
    return 0;
}