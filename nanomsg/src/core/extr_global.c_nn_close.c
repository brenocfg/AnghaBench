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
struct TYPE_2__ {int* unused; size_t nsocks; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** socks; } ;

/* Variables and functions */
 int EINTR ; 
 size_t NN_MAX_SOCKETS ; 
 int errno ; 
 int /*<<< orphan*/  nn_free (struct nn_sock*) ; 
 int nn_global_hold_socket_locked (struct nn_sock**,int) ; 
 int /*<<< orphan*/  nn_global_rele_socket (struct nn_sock*) ; 
 int /*<<< orphan*/  nn_global_term () ; 
 int /*<<< orphan*/  nn_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_sock_rele (struct nn_sock*) ; 
 int /*<<< orphan*/  nn_sock_stop (struct nn_sock*) ; 
 int nn_sock_term (struct nn_sock*) ; 
 TYPE_1__ self ; 

int nn_close (int s)
{
    int rc;
    struct nn_sock *sock;

    nn_mutex_lock (&self.lock);
    rc = nn_global_hold_socket_locked (&sock, s);
    if (nn_slow (rc < 0)) {
        nn_mutex_unlock (&self.lock);
        errno = -rc;
        return -1;
    }

    /*  Start the shutdown process on the socket.  This will cause
        all other socket users, as well as endpoints, to begin cleaning up.
        This is done with the lock held to ensure that two instances
        of nn_close can't access the same socket. */
    nn_sock_stop (sock);

    /*  We have to drop both the hold we just acquired, as well as
        the original hold, in order for nn_sock_term to complete. */
    nn_sock_rele (sock);
    nn_sock_rele (sock);
    nn_mutex_unlock (&self.lock);

    /*  Now clean up.  The termination routine below will block until
        all other consumers of the socket have dropped their holds, and
        all endpoints have cleanly exited. */
    rc = nn_sock_term (sock);
    if (nn_slow (rc == -EINTR)) {
        nn_global_rele_socket (sock);
        errno = EINTR;
        return -1;
    }

    /*  Remove the socket from the socket table, add it to unused socket
        table. */
    nn_mutex_lock (&self.lock);
    self.socks [s] = NULL;
    self.unused [NN_MAX_SOCKETS - self.nsocks] = s;
    --self.nsocks;
    nn_free (sock);

    /*  Destroy the global context if there's no socket remaining. */
    nn_global_term ();

    nn_mutex_unlock (&self.lock);

    return 0;
}