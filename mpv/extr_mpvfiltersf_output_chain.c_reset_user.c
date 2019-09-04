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
struct mp_user_filter {int error_eof_sent; int /*<<< orphan*/  last_out_pts; int /*<<< orphan*/  last_in_pts; } ;
struct mp_filter {struct mp_user_filter* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 

__attribute__((used)) static void reset_user(struct mp_filter *f)
{
    struct mp_user_filter *u = f->priv;

    u->error_eof_sent = false;
    u->last_in_pts = u->last_out_pts = MP_NOPTS_VALUE;
}