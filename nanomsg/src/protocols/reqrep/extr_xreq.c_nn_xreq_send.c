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
struct nn_sockbase {int dummy; } ;
struct nn_msg {int dummy; } ;

/* Variables and functions */
 int nn_xreq_send_to (struct nn_sockbase*,struct nn_msg*,int /*<<< orphan*/ *) ; 

int nn_xreq_send (struct nn_sockbase *self, struct nn_msg *msg)
{
    return nn_xreq_send_to (self, msg, NULL);
}