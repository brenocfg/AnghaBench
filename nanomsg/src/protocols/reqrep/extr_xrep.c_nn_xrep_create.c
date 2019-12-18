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
struct nn_xrep {struct nn_sockbase sockbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_assert (struct nn_xrep*) ; 
 struct nn_xrep* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_xrep_init (struct nn_xrep*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  nn_xrep_sockbase_vfptr ; 

__attribute__((used)) static int nn_xrep_create (void *hint, struct nn_sockbase **sockbase)
{
    struct nn_xrep *self;

    self = nn_alloc (sizeof (struct nn_xrep), "socket (xrep)");
    alloc_assert (self);
    nn_xrep_init (self, &nn_xrep_sockbase_vfptr, hint);
    *sockbase = &self->sockbase;

    return 0;
}