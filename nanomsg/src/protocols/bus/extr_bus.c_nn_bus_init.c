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
struct nn_bus {int /*<<< orphan*/  xbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_xbus_init (int /*<<< orphan*/ *,struct nn_sockbase_vfptr const*,void*) ; 

__attribute__((used)) static void nn_bus_init (struct nn_bus *self,
    const struct nn_sockbase_vfptr *vfptr, void *hint)
{
    nn_xbus_init (&self->xbus, vfptr, hint);
}