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
struct nn_transport {char const* name; } ;
struct nn_sock {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int EPROTONOSUPPORT ; 
 size_t NN_SOCKADDR_MAX ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 int nn_sock_add_ep (struct nn_sock*,struct nn_transport const*,int,char const*) ; 
 struct nn_transport** nn_transports ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int nn_global_create_ep (struct nn_sock *sock, const char *addr,
    int bind)
{
    int rc;
    const char *proto;
    const char *delim;
    size_t protosz;
    const struct nn_transport *tp;
    int i;

    /*  Check whether address is valid. */
    if (!addr)
        return -EINVAL;
    if (strlen (addr) >= NN_SOCKADDR_MAX)
        return -ENAMETOOLONG;

    /*  Separate the protocol and the actual address. */
    proto = addr;
    delim = strchr (addr, ':');
    if (!delim)
        return -EINVAL;
    if (delim [1] != '/' || delim [2] != '/')
        return -EINVAL;
    protosz = delim - addr;
    addr += protosz + 3;

    /*  Find the specified protocol. */
    tp = NULL;
    for (i = 0; ((tp = nn_transports[i]) != NULL); i++) {
        if (strlen (tp->name) == protosz &&
              memcmp (tp->name, proto, protosz) == 0)
            break;
    }

    /*  The protocol specified doesn't match any known protocol. */
    if (tp == NULL) {
        return -EPROTONOSUPPORT;
    }

    /*  Ask the socket to create the endpoint. */
    rc = nn_sock_add_ep (sock, tp, bind, addr);
    return rc;
}