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
struct mp_pin {struct mp_pin* user_conn; struct mp_pin* other; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mp_pin *find_connected_end(struct mp_pin *p)
{
    while (1) {
        struct mp_pin *other = p->other;
        if (!other->user_conn)
            return other;
        p = other->user_conn;
    }
    assert(0);
}