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
struct TYPE_2__ {int established_connections; int accepted_connections; int dropped_connections; int broken_connections; int connect_errors; int bind_errors; int accept_errors; int messages_sent; int messages_received; int bytes_sent; int bytes_received; int current_connections; int inprogress_connections; int current_snd_priority; int current_ep_errors; } ;
struct nn_sock {TYPE_1__ statistics; } ;
typedef  int int64_t ;

/* Variables and functions */
 int INT_MAX ; 
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
 int /*<<< orphan*/  nn_assert (int) ; 

void nn_sock_stat_increment (struct nn_sock *self, int name, int64_t increment)
{
    switch (name) {
        case NN_STAT_ESTABLISHED_CONNECTIONS:
            nn_assert (increment > 0);
            self->statistics.established_connections += increment;
            break;
        case NN_STAT_ACCEPTED_CONNECTIONS:
            nn_assert (increment > 0);
            self->statistics.accepted_connections += increment;
            break;
        case NN_STAT_DROPPED_CONNECTIONS:
            nn_assert (increment > 0);
            self->statistics.dropped_connections += increment;
            break;
        case NN_STAT_BROKEN_CONNECTIONS:
            nn_assert (increment > 0);
            self->statistics.broken_connections += increment;
            break;
        case NN_STAT_CONNECT_ERRORS:
            nn_assert (increment > 0);
            self->statistics.connect_errors += increment;
            break;
        case NN_STAT_BIND_ERRORS:
            nn_assert (increment > 0);
            self->statistics.bind_errors += increment;
            break;
        case NN_STAT_ACCEPT_ERRORS:
            nn_assert (increment > 0);
            self->statistics.accept_errors += increment;
            break;
        case NN_STAT_MESSAGES_SENT:
            nn_assert (increment > 0);
            self->statistics.messages_sent += increment;
            break;
        case NN_STAT_MESSAGES_RECEIVED:
            nn_assert (increment > 0);
            self->statistics.messages_received += increment;
            break;
        case NN_STAT_BYTES_SENT:
            nn_assert (increment >= 0);
            self->statistics.bytes_sent += increment;
            break;
        case NN_STAT_BYTES_RECEIVED:
            nn_assert (increment >= 0);
            self->statistics.bytes_received += increment;
            break;

        case NN_STAT_CURRENT_CONNECTIONS:
            nn_assert (increment > 0 ||
                self->statistics.current_connections >= -increment);
            nn_assert(increment < INT_MAX && increment > -INT_MAX);
            self->statistics.current_connections += (int) increment;
            break;
        case NN_STAT_INPROGRESS_CONNECTIONS:
            nn_assert (increment > 0 ||
                self->statistics.inprogress_connections >= -increment);
            nn_assert(increment < INT_MAX && increment > -INT_MAX);
            self->statistics.inprogress_connections += (int) increment;
            break;
        case NN_STAT_CURRENT_SND_PRIORITY:
            /*  This is an exception, we don't want to increment priority  */
            nn_assert((increment > 0 && increment <= 16) || increment == -1);
            self->statistics.current_snd_priority = (int) increment;
            break;
        case NN_STAT_CURRENT_EP_ERRORS:
            nn_assert (increment > 0 ||
                self->statistics.current_ep_errors >= -increment);
            nn_assert(increment < INT_MAX && increment > -INT_MAX);
            self->statistics.current_ep_errors += (int) increment;
            break;
    }
}