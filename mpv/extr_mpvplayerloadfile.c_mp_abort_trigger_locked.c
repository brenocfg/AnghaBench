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
struct mp_abort_entry {int /*<<< orphan*/  cancel; } ;
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_cancel_trigger (int /*<<< orphan*/ ) ; 

void mp_abort_trigger_locked(struct MPContext *mpctx,
                             struct mp_abort_entry *abort)
{
    mp_cancel_trigger(abort->cancel);
}