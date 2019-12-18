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
struct nn_sock {int dummy; } ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_global_hold_socket (struct nn_sock**,int) ; 
 int /*<<< orphan*/  nn_global_rele_socket (struct nn_sock*) ; 
 scalar_t__ nn_slow (int) ; 
 int nn_sock_rm_ep (struct nn_sock*,int) ; 

int nn_shutdown (int s, int how)
{
    int rc;
    struct nn_sock *sock;

    rc = nn_global_hold_socket (&sock, s);
    if (nn_slow (rc < 0)) {
        errno = -rc;
        return -1;
    }

    rc = nn_sock_rm_ep (sock, how);
    if (nn_slow (rc < 0)) {
        nn_global_rele_socket (sock);
        errno = -rc;
        return -1;
    }
    nn_assert (rc == 0);

    nn_global_rele_socket (sock);
    return 0;
}