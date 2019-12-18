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
struct nn_xpair {struct nn_sockbase sockbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_assert (struct nn_xpair*) ; 
 struct nn_xpair* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_xpair_init (struct nn_xpair*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  nn_xpair_sockbase_vfptr ; 

int nn_xpair_create (void *hint, struct nn_sockbase **sockbase)
{
    struct nn_xpair *self;

    self = nn_alloc (sizeof (struct nn_xpair), "socket (pair)");
    alloc_assert (self);
    nn_xpair_init (self, &nn_xpair_sockbase_vfptr, hint);
    *sockbase = &self->sockbase;

    return 0;
}