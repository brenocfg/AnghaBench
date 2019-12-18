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
struct nn_sockbase {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_sock_stopped (int /*<<< orphan*/ ) ; 

void nn_sockbase_stopped (struct nn_sockbase *self)
{
    nn_sock_stopped (self->sock);
}