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
struct TYPE_3__ {size_t alloc; char* buf; int fixed_buf; scalar_t__ len; } ;
typedef  TYPE_1__ vstr_t ;

/* Variables and functions */

void vstr_init_fixed_buf(vstr_t *vstr, size_t alloc, char *buf) {
    vstr->alloc = alloc;
    vstr->len = 0;
    vstr->buf = buf;
    vstr->fixed_buf = true;
}