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
 int nn_global_create_ep (struct nn_sock*,char const*,int) ; 
 int nn_global_hold_socket (struct nn_sock**,int) ; 
 int /*<<< orphan*/  nn_global_rele_socket (struct nn_sock*) ; 
 scalar_t__ nn_slow (int) ; 

int nn_bind (int s, const char *addr)
{
    int rc;
    struct nn_sock *sock;

    rc = nn_global_hold_socket (&sock, s);
    if (rc < 0) {
        errno = -rc;
        return -1;
    }

    rc = nn_global_create_ep (sock, addr, 1);
    if (nn_slow (rc < 0)) {
        nn_global_rele_socket (sock);
        errno = -rc;
        return -1;
    }

    nn_global_rele_socket (sock);
    return rc;
}