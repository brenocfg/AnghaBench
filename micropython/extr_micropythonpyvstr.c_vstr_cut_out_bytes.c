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
struct TYPE_3__ {size_t len; scalar_t__ buf; } ;
typedef  TYPE_1__ vstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 

void vstr_cut_out_bytes(vstr_t *vstr, size_t byte_pos, size_t bytes_to_cut) {
    if (byte_pos >= vstr->len) {
        return;
    } else if (byte_pos + bytes_to_cut >= vstr->len) {
        vstr->len = byte_pos;
    } else {
        memmove(vstr->buf + byte_pos, vstr->buf + byte_pos + bytes_to_cut, vstr->len - byte_pos - bytes_to_cut);
        vstr->len -= bytes_to_cut;
    }
}