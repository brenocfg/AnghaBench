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
struct mp_pin {scalar_t__ dir; struct mp_pin* user_conn; } ;

/* Variables and functions */
 scalar_t__ MP_PIN_IN ; 
 scalar_t__ MP_PIN_OUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  init_connection (struct mp_pin*) ; 
 int /*<<< orphan*/  mp_pin_disconnect (struct mp_pin*) ; 

void mp_pin_connect(struct mp_pin *dst, struct mp_pin *src)
{
    assert(src->dir == MP_PIN_OUT);
    assert(dst->dir == MP_PIN_IN);

    if (dst->user_conn == src) {
        assert(src->user_conn == dst);
        return;
    }

    mp_pin_disconnect(src);
    mp_pin_disconnect(dst);

    src->user_conn = dst;
    dst->user_conn = src;

    init_connection(src);
}