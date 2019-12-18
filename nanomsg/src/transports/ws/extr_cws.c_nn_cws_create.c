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
typedef  char uint8_t ;
struct sockaddr_storage {int dummy; } ;
struct nn_ep {int dummy; } ;
struct nn_cws {int remote_hostname_len; int remote_port; char msg_type; int /*<<< orphan*/  fsm; int /*<<< orphan*/  dns; int /*<<< orphan*/  sws; int /*<<< orphan*/  retry; int /*<<< orphan*/  usock; int /*<<< orphan*/  state; int /*<<< orphan*/  resource; int /*<<< orphan*/  nic; int /*<<< orphan*/  remote_host; scalar_t__ peer_gone; struct nn_ep* ep; } ;
typedef  int /*<<< orphan*/  reconnect_ivl_max ;
typedef  int /*<<< orphan*/  reconnect_ivl ;
typedef  int /*<<< orphan*/  msg_type ;
typedef  int /*<<< orphan*/  ipv4only ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  NN_CWS_SRC_DNS ; 
 int /*<<< orphan*/  NN_CWS_SRC_RECONNECT_TIMER ; 
 int /*<<< orphan*/  NN_CWS_SRC_SWS ; 
 int /*<<< orphan*/  NN_CWS_SRC_USOCK ; 
 int /*<<< orphan*/  NN_CWS_STATE_IDLE ; 
 int /*<<< orphan*/  NN_IPV4ONLY ; 
 int /*<<< orphan*/  NN_RECONNECT_IVL ; 
 int /*<<< orphan*/  NN_RECONNECT_IVL_MAX ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_WS ; 
 int /*<<< orphan*/  NN_WS_MSG_TYPE ; 
 int /*<<< orphan*/  alloc_assert (struct nn_cws*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 struct nn_cws* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_backoff_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nn_chunkref_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_chunkref_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_cws_ep_ops ; 
 int /*<<< orphan*/  nn_cws_handler ; 
 int /*<<< orphan*/  nn_cws_shutdown ; 
 scalar_t__ nn_dns_check_hostname (char const*,int) ; 
 int /*<<< orphan*/  nn_dns_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* nn_ep_getaddr (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_getctx (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_getopt (struct nn_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_ep_tran_setup (struct nn_ep*,int /*<<< orphan*/ *,struct nn_cws*) ; 
 int /*<<< orphan*/  nn_free (struct nn_cws*) ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int nn_iface_resolve (char const*,int,int,struct sockaddr_storage*,size_t*) ; 
 scalar_t__ nn_literal_resolve (char const*,int,int,struct sockaddr_storage*,size_t*) ; 
 int nn_port_resolve (char const*,int) ; 
 int /*<<< orphan*/  nn_sws_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nn_ep*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,char const*,int) ; 
 char* strrchr (char const*,char) ; 

int nn_cws_create (struct nn_ep *ep)
{
    int rc;
    const char *addr;
    size_t addrlen;
    const char *semicolon;
    const char *hostname;
    size_t hostlen;
    const char *colon;
    const char *slash;
    const char *resource;
    size_t resourcelen;
    struct sockaddr_storage ss;
    size_t sslen;
    int ipv4only;
    size_t ipv4onlylen;
    struct nn_cws *self;
    int reconnect_ivl;
    int reconnect_ivl_max;
    int msg_type;
    size_t sz;

    /*  Allocate the new endpoint object. */
    self = nn_alloc (sizeof (struct nn_cws), "cws");
    alloc_assert (self);
    self->ep = ep;
    self->peer_gone = 0;

    /*  Initalise the endpoint. */
    nn_ep_tran_setup (ep, &nn_cws_ep_ops, self);

    /*  Check whether IPv6 is to be used. */
    ipv4onlylen = sizeof (ipv4only);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_IPV4ONLY, &ipv4only, &ipv4onlylen);
    nn_assert (ipv4onlylen == sizeof (ipv4only));

    /*  Start parsing the address. */
    addr = nn_ep_getaddr (ep);
    addrlen = strlen (addr);
    semicolon = strchr (addr, ';');
    hostname = semicolon ? semicolon + 1 : addr;
    colon = strrchr (addr, ':');
    slash = colon ? strchr (colon, '/') : strchr (addr, '/');
    resource = slash ? slash : addr + addrlen;
    self->remote_hostname_len = colon ? colon - hostname : resource - hostname;

    /*  Host contains both hostname and port. */
    hostlen = resource - hostname;

    /*  Parse the port; assume port 80 if not explicitly declared. */
    if (colon != NULL) {
        rc = nn_port_resolve (colon + 1, resource - colon - 1);
        if (rc < 0) {
            nn_free(self);
            return -EINVAL;
        }
        self->remote_port = rc;
    }
    else {
        self->remote_port = 80;
    }

    /*  Check whether the host portion of the address is either a literal
        or a valid hostname. */
    if (nn_dns_check_hostname (hostname, self->remote_hostname_len) < 0 &&
          nn_literal_resolve (hostname, self->remote_hostname_len, ipv4only,
          &ss, &sslen) < 0) {
        nn_free(self);
        return -EINVAL;
    }

    /*  If local address is specified, check whether it is valid. */
    if (semicolon) {
        rc = nn_iface_resolve (addr, semicolon - addr, ipv4only, &ss, &sslen);
        if (rc < 0) {
            nn_free(self);
            return -ENODEV;
        }
    }

    /*  At this point, the address is valid, so begin allocating resources. */
    nn_chunkref_init (&self->remote_host, hostlen + 1);
    memcpy (nn_chunkref_data (&self->remote_host), hostname, hostlen);
    ((uint8_t *) nn_chunkref_data (&self->remote_host)) [hostlen] = '\0';

    if (semicolon) {
        nn_chunkref_init (&self->nic, semicolon - addr);
        memcpy (nn_chunkref_data (&self->nic),
            addr, semicolon - addr);
    }
    else {
        nn_chunkref_init (&self->nic, 1);
        memcpy (nn_chunkref_data (&self->nic), "*", 1);
    }

    /*  The requested resource is used in opening handshake. */
    resourcelen = strlen (resource);
    if (resourcelen) {
        nn_chunkref_init (&self->resource, resourcelen + 1);
        strncpy (nn_chunkref_data (&self->resource),
            resource, resourcelen + 1);
    }
    else {
        /*  No resource specified, so allocate base path. */
        nn_chunkref_init (&self->resource, 2);
        strncpy (nn_chunkref_data (&self->resource), "/", 2);
    }

    /*  Initialise the structure. */
    nn_fsm_init_root (&self->fsm, nn_cws_handler, nn_cws_shutdown,
        nn_ep_getctx (ep));
    self->state = NN_CWS_STATE_IDLE;
    nn_usock_init (&self->usock, NN_CWS_SRC_USOCK, &self->fsm);

    sz = sizeof (msg_type);
    nn_ep_getopt (ep, NN_WS, NN_WS_MSG_TYPE, &msg_type, &sz);
    nn_assert (sz == sizeof (msg_type));
    self->msg_type = (uint8_t) msg_type;

    sz = sizeof (reconnect_ivl);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_RECONNECT_IVL, &reconnect_ivl, &sz);
    nn_assert (sz == sizeof (reconnect_ivl));
    sz = sizeof (reconnect_ivl_max);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_RECONNECT_IVL_MAX,
        &reconnect_ivl_max, &sz);
    nn_assert (sz == sizeof (reconnect_ivl_max));
    if (reconnect_ivl_max == 0)
        reconnect_ivl_max = reconnect_ivl;
    nn_backoff_init (&self->retry, NN_CWS_SRC_RECONNECT_TIMER,
        reconnect_ivl, reconnect_ivl_max, &self->fsm);

    nn_sws_init (&self->sws, NN_CWS_SRC_SWS, ep, &self->fsm);
    nn_dns_init (&self->dns, NN_CWS_SRC_DNS, &self->fsm);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    return 0;
}