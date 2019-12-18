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
struct nn_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int nn_global_hold_socket_locked (struct nn_sock**,int) ; 
 int /*<<< orphan*/  nn_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ self ; 

int nn_global_hold_socket(struct nn_sock **sockp, int s)
{
    int rc;
    nn_mutex_lock(&self.lock);
    rc = nn_global_hold_socket_locked(sockp, s);
    nn_mutex_unlock(&self.lock);
    return rc;
}