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
struct nn_ep {scalar_t__ last_errno; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_STAT_CURRENT_EP_ERRORS ; 
 int /*<<< orphan*/  nn_sock_report_error (int /*<<< orphan*/ ,struct nn_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_sock_stat_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void nn_ep_clear_error (struct nn_ep *self)
{
    if (self->last_errno == 0)
        /*  Error is already clear, no need to report it  */
        return;
    nn_sock_stat_increment (self->sock, NN_STAT_CURRENT_EP_ERRORS, -1);
    self->last_errno = 0;
    nn_sock_report_error (self->sock, self, 0);
}