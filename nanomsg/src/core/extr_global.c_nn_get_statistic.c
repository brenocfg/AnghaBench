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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  current_ep_errors; int /*<<< orphan*/  current_snd_priority; int /*<<< orphan*/  inprogress_connections; int /*<<< orphan*/  current_connections; int /*<<< orphan*/  bytes_received; int /*<<< orphan*/  bytes_sent; int /*<<< orphan*/  messages_received; int /*<<< orphan*/  messages_sent; int /*<<< orphan*/  bind_errors; int /*<<< orphan*/  connect_errors; int /*<<< orphan*/  broken_connections; int /*<<< orphan*/  dropped_connections; int /*<<< orphan*/  accepted_connections; int /*<<< orphan*/  established_connections; } ;
struct nn_sock {TYPE_1__ statistics; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NN_STAT_ACCEPTED_CONNECTIONS 142 
#define  NN_STAT_ACCEPT_ERRORS 141 
#define  NN_STAT_BIND_ERRORS 140 
#define  NN_STAT_BROKEN_CONNECTIONS 139 
#define  NN_STAT_BYTES_RECEIVED 138 
#define  NN_STAT_BYTES_SENT 137 
#define  NN_STAT_CONNECT_ERRORS 136 
#define  NN_STAT_CURRENT_CONNECTIONS 135 
#define  NN_STAT_CURRENT_EP_ERRORS 134 
#define  NN_STAT_CURRENT_SND_PRIORITY 133 
#define  NN_STAT_DROPPED_CONNECTIONS 132 
#define  NN_STAT_ESTABLISHED_CONNECTIONS 131 
#define  NN_STAT_INPROGRESS_CONNECTIONS 130 
#define  NN_STAT_MESSAGES_RECEIVED 129 
#define  NN_STAT_MESSAGES_SENT 128 
 int errno ; 
 int nn_global_hold_socket (struct nn_sock**,int) ; 
 int /*<<< orphan*/  nn_global_rele_socket (struct nn_sock*) ; 
 scalar_t__ nn_slow (int) ; 

uint64_t nn_get_statistic (int s, int statistic)
{
    int rc;
    struct nn_sock *sock;
    uint64_t val;

    rc = nn_global_hold_socket (&sock, s);
    if (nn_slow (rc < 0)) {
        errno = -rc;
        return (uint64_t)-1;
    }

    switch (statistic) {
    case NN_STAT_ESTABLISHED_CONNECTIONS:
        val = sock->statistics.established_connections;
        break;
    case NN_STAT_ACCEPTED_CONNECTIONS:
        val = sock->statistics.accepted_connections;
        break;
    case NN_STAT_DROPPED_CONNECTIONS:
        val = sock->statistics.dropped_connections;
        break;
    case NN_STAT_BROKEN_CONNECTIONS:
        val = sock->statistics.broken_connections;
        break;
    case NN_STAT_CONNECT_ERRORS:
        val = sock->statistics.connect_errors;
        break;
    case NN_STAT_BIND_ERRORS:
        val = sock->statistics.bind_errors;
        break;
    case NN_STAT_ACCEPT_ERRORS:
        val = sock->statistics.bind_errors;
        break;
    case NN_STAT_MESSAGES_SENT:
        val = sock->statistics.messages_sent;
        break;
    case NN_STAT_MESSAGES_RECEIVED:
        val = sock->statistics.messages_received;
        break;
    case NN_STAT_BYTES_SENT:
        val = sock->statistics.bytes_sent;
        break;
    case NN_STAT_BYTES_RECEIVED:
        val = sock->statistics.bytes_received;
        break;
    case NN_STAT_CURRENT_CONNECTIONS:
        val = sock->statistics.current_connections;
        break;
    case NN_STAT_INPROGRESS_CONNECTIONS:
        val = sock->statistics.inprogress_connections;
        break;
    case NN_STAT_CURRENT_SND_PRIORITY:
        val = sock->statistics.current_snd_priority;
        break;
    case NN_STAT_CURRENT_EP_ERRORS:
        val = sock->statistics.current_ep_errors;
        break;
    default:
        val = (uint64_t)-1;
        errno = EINVAL;
        break;
    }

    nn_global_rele_socket (sock);
    return val;
}