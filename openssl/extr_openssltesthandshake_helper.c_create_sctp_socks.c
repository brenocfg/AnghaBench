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
typedef  int /*<<< orphan*/  const BIO_ADDRINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDRINFO_address (int /*<<< orphan*/  const*) ; 
 int BIO_ADDRINFO_family (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BIO_ADDRINFO_next (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_LOOKUP_CLIENT ; 
 int /*<<< orphan*/  BIO_LOOKUP_SERVER ; 
 int /*<<< orphan*/  BIO_SOCK_NONBLOCK ; 
 int /*<<< orphan*/  BIO_SOCK_REUSEADDR ; 
 int BIO_accept_ex (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_closesocket (int) ; 
 int /*<<< orphan*/  BIO_connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_listen (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_lookup_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int BIO_sock_init () ; 
 int BIO_socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_socket_nbio (int,int) ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  set_sock_as_sctp (int) ; 

__attribute__((used)) static int create_sctp_socks(int *ssock, int *csock)
{
    BIO_ADDRINFO *res = NULL;
    const BIO_ADDRINFO *ai = NULL;
    int lsock = INVALID_SOCKET, asock = INVALID_SOCKET;
    int consock = INVALID_SOCKET;
    int ret = 0;
    int family = 0;

    if (BIO_sock_init() != 1)
        return 0;

    /*
     * Port is 4463. It could be anything. It will fail if it's already being
     * used for some other SCTP service. It seems unlikely though so we don't
     * worry about it here.
     */
    if (!BIO_lookup_ex(NULL, "4463", BIO_LOOKUP_SERVER, family, SOCK_STREAM,
                       IPPROTO_SCTP, &res))
        return 0;

    for (ai = res; ai != NULL; ai = BIO_ADDRINFO_next(ai)) {
        family = BIO_ADDRINFO_family(ai);
        lsock = BIO_socket(family, SOCK_STREAM, IPPROTO_SCTP, 0);
        if (lsock == INVALID_SOCKET) {
            /* Maybe the kernel doesn't support the socket family, even if
             * BIO_lookup() added it in the returned result...
             */
            continue;
        }

        if (!set_sock_as_sctp(lsock)
                || !BIO_listen(lsock, BIO_ADDRINFO_address(ai),
                               BIO_SOCK_REUSEADDR)) {
            BIO_closesocket(lsock);
            lsock = INVALID_SOCKET;
            continue;
        }

        /* Success, don't try any more addresses */
        break;
    }

    if (lsock == INVALID_SOCKET)
        goto err;

    BIO_ADDRINFO_free(res);
    res = NULL;

    if (!BIO_lookup_ex(NULL, "4463", BIO_LOOKUP_CLIENT, family, SOCK_STREAM,
                        IPPROTO_SCTP, &res))
        goto err;

    consock = BIO_socket(family, SOCK_STREAM, IPPROTO_SCTP, 0);
    if (consock == INVALID_SOCKET)
        goto err;

    if (!set_sock_as_sctp(consock)
            || !BIO_connect(consock, BIO_ADDRINFO_address(res), 0)
            || !BIO_socket_nbio(consock, 1))
        goto err;

    asock = BIO_accept_ex(lsock, NULL, BIO_SOCK_NONBLOCK);
    if (asock == INVALID_SOCKET)
        goto err;

    *csock = consock;
    *ssock = asock;
    consock = asock = INVALID_SOCKET;
    ret = 1;

 err:
    BIO_ADDRINFO_free(res);
    if (consock != INVALID_SOCKET)
        BIO_closesocket(consock);
    if (lsock != INVALID_SOCKET)
        BIO_closesocket(lsock);
    if (asock != INVALID_SOCKET)
        BIO_closesocket(asock);
    return ret;
}