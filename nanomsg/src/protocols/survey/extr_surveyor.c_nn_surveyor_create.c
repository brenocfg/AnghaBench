#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nn_sockbase {int dummy; } ;
struct TYPE_2__ {struct nn_sockbase sockbase; } ;
struct nn_surveyor {TYPE_1__ xsurveyor; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_assert (struct nn_surveyor*) ; 
 struct nn_surveyor* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_surveyor_init (struct nn_surveyor*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  nn_surveyor_sockbase_vfptr ; 

__attribute__((used)) static int nn_surveyor_create (void *hint, struct nn_sockbase **sockbase)
{
    struct nn_surveyor *self;

    self = nn_alloc (sizeof (struct nn_surveyor), "socket (surveyor)");
    alloc_assert (self);
    nn_surveyor_init (self, &nn_surveyor_sockbase_vfptr, hint);
    *sockbase = &self->xsurveyor.sockbase;

    return 0;
}