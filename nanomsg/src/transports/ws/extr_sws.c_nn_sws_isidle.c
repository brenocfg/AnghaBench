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
struct nn_sws {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int nn_fsm_isidle (int /*<<< orphan*/ *) ; 

int nn_sws_isidle (struct nn_sws *self)
{
    return nn_fsm_isidle (&self->fsm);
}