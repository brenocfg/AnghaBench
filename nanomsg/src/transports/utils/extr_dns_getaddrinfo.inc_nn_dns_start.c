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
struct nn_dns_result {char addr; size_t addrlen; int /*<<< orphan*/  error; } ;
struct nn_dns {int /*<<< orphan*/  fsm; struct nn_dns_result* result; } ;
struct addrinfo {char const* ai_addr; size_t ai_addrlen; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  query ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AI_V4MAPPED ; 
 int EINVAL ; 
 int /*<<< orphan*/  NN_DNS_STATE_IDLE ; 
 int NN_SOCKADDR_MAX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_dns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int nn_literal_resolve (char const*,size_t,int,char*,size_t*) ; 

void nn_dns_start (struct nn_dns *self, const char *addr, size_t addrlen,
    int ipv4only, struct nn_dns_result *result)
{
    int rc;
    struct addrinfo query;
    struct addrinfo *reply;
    char hostname [NN_SOCKADDR_MAX];

    nn_assert_state (self, NN_DNS_STATE_IDLE);

    self->result = result;

    /*  Try to resolve the supplied string as a literal address. In this case,
        there's no DNS lookup involved. */
    rc = nn_literal_resolve (addr, addrlen, ipv4only, &self->result->addr,
        &self->result->addrlen);
    if (rc == 0) {
        self->result->error = 0;
        nn_fsm_start (&self->fsm);
        return;
    }
    errnum_assert (rc == -EINVAL, -rc);

    /*  The name is not a literal. Let's do an actual DNS lookup. */
    memset (&query, 0, sizeof (query));
    if (ipv4only)
        query.ai_family = AF_INET;
    else {
        query.ai_family = AF_INET6;
#ifdef AI_V4MAPPED
        query.ai_flags = AI_V4MAPPED;
#endif
    }
    nn_assert (sizeof (hostname) > addrlen);
    query.ai_socktype = SOCK_STREAM;
    memcpy (hostname, addr, addrlen);
    hostname [addrlen] = 0;

    /*  Perform the DNS lookup itself. */
    self->result->error = getaddrinfo (hostname, NULL, &query, &reply);
    if (self->result->error) {
        nn_fsm_start (&self->fsm);
        return;
    }

    /*  Take just the first address and store it.  (RFC recommends that we
        iterate through addresses until one works, but that doesn't match
        our state model.  This is the best we can do.) */
    self->result->error = 0;
    memcpy (&self->result->addr, reply->ai_addr, reply->ai_addrlen);
    self->result->addrlen = reply->ai_addrlen;
    freeaddrinfo (reply);

    nn_fsm_start (&self->fsm);
}