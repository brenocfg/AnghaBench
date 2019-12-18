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
struct nn_socktype {int domain; int protocol; } ;
struct nn_sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ nsocks; int* unused; struct nn_sock** socks; } ;

/* Variables and functions */
 int AF_SP ; 
 int AF_SP_RAW ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int EMFILE ; 
 int ENOMEM ; 
 scalar_t__ NN_MAX_SOCKETS ; 
 struct nn_sock* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_free (struct nn_sock*) ; 
 int nn_sock_init (struct nn_sock*,struct nn_socktype const*,int) ; 
 struct nn_socktype** nn_socktypes ; 
 TYPE_1__ self ; 

int nn_global_create_socket (int domain, int protocol)
{
    int rc;
    int s;
    int i;
    const struct nn_socktype *socktype;
    struct nn_sock *sock;

    /* The function is called with lock held */

    /*  Only AF_SP and AF_SP_RAW domains are supported. */
    if (domain != AF_SP && domain != AF_SP_RAW) {
        return -EAFNOSUPPORT;
    }

    /*  If socket limit was reached, report error. */
    if (self.nsocks >= NN_MAX_SOCKETS) {
        return -EMFILE;
    }

    /*  Find an empty socket slot. */
    s = self.unused [NN_MAX_SOCKETS - self.nsocks - 1];

    /*  Find the appropriate socket type. */
    for (i = 0; (socktype = nn_socktypes[i]) != NULL; i++) {
        if (socktype->domain == domain && socktype->protocol == protocol) {

            /*  Instantiate the socket. */
            if ((sock = nn_alloc (sizeof (struct nn_sock), "sock")) == NULL)
                return -ENOMEM;
            rc = nn_sock_init (sock, socktype, s);
            if (rc < 0) {
                nn_free (sock);
                return rc;
            }

            /*  Adjust the global socket table. */
            self.socks [s] = sock;
            ++self.nsocks;
            return s;
        }
    }
    /*  Specified socket type wasn't found. */
    return -EINVAL;
}