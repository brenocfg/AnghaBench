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
struct mp_pin {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_EOF_FRAME ; 
 int /*<<< orphan*/  mp_pin_out_unread (struct mp_pin*,int /*<<< orphan*/ ) ; 

void mp_pin_out_repeat_eof(struct mp_pin *p)
{
    mp_pin_out_unread(p, MP_EOF_FRAME);
}