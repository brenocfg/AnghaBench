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
struct socks_proxy_info {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  socket_descriptor_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int D_LINK_ERRORS ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int M_ERRNO ; 
 int SIGUSR1 ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int port_from_servname (char const*) ; 
 int /*<<< orphan*/  recv_socks_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int volatile*) ; 
 scalar_t__ send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socks_handshake (struct socks_proxy_info*,int /*<<< orphan*/ ,int volatile*) ; 
 size_t strlen (char const*) ; 

void
establish_socks_proxy_passthru(struct socks_proxy_info *p,
                               socket_descriptor_t sd,  /* already open to proxy */
                               const char *host,        /* openvpn server remote */
                               const char *servname,    /* openvpn server port */
                               volatile int *signal_received)
{
    char buf[128];
    size_t len;

    if (!socks_handshake(p, sd, signal_received))
    {
        goto error;
    }

    /* format Socks CONNECT message */
    buf[0] = '\x05';            /* VER = 5 */
    buf[1] = '\x01';            /* CMD = 1 (CONNECT) */
    buf[2] = '\x00';            /* RSV */
    buf[3] = '\x03';            /* ATYP = 3 (DOMAINNAME) */

    len = strlen(host);
    len = (5 + len + 2 > sizeof(buf)) ? (sizeof(buf) - 5 - 2) : len;

    buf[4] = (char) len;
    memcpy(buf + 5, host, len);

    int port = port_from_servname(servname);
    if (port ==0)
    {
        msg(D_LINK_ERRORS, "establish_socks_proxy_passthrough: Cannot convert %s to port number", servname);
        goto error;
    }

    buf[5 + len] = (char) (port >> 8);
    buf[5 + len + 1] = (char) (port & 0xff);

    {
        const ssize_t size = send(sd, buf, 5 + len + 2, MSG_NOSIGNAL);
        if ((int)size != 5 + (int)len + 2)
        {
            msg(D_LINK_ERRORS | M_ERRNO, "establish_socks_proxy_passthru: TCP port write failed on send()");
            goto error;
        }
    }


    /* receive reply from Socks proxy and discard */
    if (!recv_socks_reply(sd, NULL, signal_received))
    {
        goto error;
    }

    return;

error:
    if (!*signal_received)
    {
        *signal_received = SIGUSR1; /* SOFT-SIGUSR1 -- socks error */
    }
    return;
}