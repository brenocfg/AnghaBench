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
struct nn_cws {int /*<<< orphan*/  state; int /*<<< orphan*/  dns_result; int /*<<< orphan*/  remote_hostname_len; int /*<<< orphan*/  dns; int /*<<< orphan*/  remote_host; int /*<<< orphan*/  ep; } ;
typedef  int /*<<< orphan*/  ipv4only ;

/* Variables and functions */
 int /*<<< orphan*/  NN_CWS_STATE_RESOLVING ; 
 int /*<<< orphan*/  NN_IPV4ONLY ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 char* nn_chunkref_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_dns_start (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ep_getopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void nn_cws_start_resolving (struct nn_cws *self)
{
    int ipv4only;
    size_t ipv4onlylen;
    char *host;

    /*  Check whether IPv6 is to be used. */
    ipv4onlylen = sizeof (ipv4only);
    nn_ep_getopt (self->ep, NN_SOL_SOCKET, NN_IPV4ONLY,
        &ipv4only, &ipv4onlylen);
    nn_assert (ipv4onlylen == sizeof (ipv4only));

    host = nn_chunkref_data (&self->remote_host);
    nn_assert (strlen (host) > 0);

    nn_dns_start (&self->dns, host, self->remote_hostname_len, ipv4only,
        &self->dns_result);

    self->state = NN_CWS_STATE_RESOLVING;
}