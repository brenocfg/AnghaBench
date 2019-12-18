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
struct TYPE_2__ {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ETERM ; 
 int NN_CTX_FLAG_TERM ; 
 int errno ; 
 int /*<<< orphan*/  nn_do_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nn_global_create_socket (int,int) ; 
 int /*<<< orphan*/  nn_global_init () ; 
 int /*<<< orphan*/  nn_global_term () ; 
 int /*<<< orphan*/  nn_lib_init ; 
 int /*<<< orphan*/  nn_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  once ; 
 TYPE_1__ self ; 

int nn_socket (int domain, int protocol)
{
    int rc;

    nn_do_once (&once, nn_lib_init);

    nn_mutex_lock (&self.lock);

    /*  If nn_term() was already called, return ETERM. */
    if (nn_slow (self.flags & NN_CTX_FLAG_TERM)) {
        nn_mutex_unlock (&self.lock);
        errno = ETERM;
        return -1;
    }

    /*  Make sure that global state is initialised. */
    nn_global_init ();

    rc = nn_global_create_socket (domain, protocol);

    if (rc < 0) {
        nn_global_term ();
        nn_mutex_unlock (&self.lock);
        errno = -rc;
        return -1;
    }

    nn_mutex_unlock (&self.lock);

    return rc;
}