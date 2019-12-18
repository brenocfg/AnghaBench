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
struct nn_sockbase_vfptr {int dummy; } ;
struct nn_sockbase {struct nn_sock* sock; struct nn_sockbase_vfptr const* vfptr; } ;
struct nn_sock {int dummy; } ;

/* Variables and functions */

void nn_sockbase_init (struct nn_sockbase *self,
    const struct nn_sockbase_vfptr *vfptr, void *hint)
{
    self->vfptr = vfptr;
    self->sock = (struct nn_sock*) hint;
}