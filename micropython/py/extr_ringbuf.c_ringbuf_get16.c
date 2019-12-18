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
typedef  int uint16_t ;
struct TYPE_3__ {int iget; int iput; size_t size; int* buf; } ;
typedef  TYPE_1__ ringbuf_t ;

/* Variables and functions */

int ringbuf_get16(ringbuf_t *r) {
    if (r->iget == r->iput) {
        return -1;
    }
    uint32_t iget_a = r->iget + 1;
    if (iget_a == r->size) {
        iget_a = 0;
    }
    if (iget_a == r->iput) {
        return -1;
    }
    uint16_t v = (r->buf[r->iget] << 8) | (r->buf[iget_a]);
    r->iget = iget_a + 1;
    if (r->iget == r->size) {
        r->iget = 0;
    }
    return v;
}