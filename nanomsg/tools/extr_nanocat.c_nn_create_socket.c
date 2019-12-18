#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int socket_type; int send_timeout; scalar_t__ recv_timeout; int* socket_name; } ;
typedef  TYPE_1__ nn_options_t ;
typedef  int /*<<< orphan*/  millis ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_SNDTIMEO ; 
 int /*<<< orphan*/  NN_SOCKET_NAME ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
#define  NN_SUB 128 
 int /*<<< orphan*/  nn_assert_errno (int,char*) ; 
 int /*<<< orphan*/  nn_set_recv_timeout (int,int) ; 
 int nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int nn_socket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_sub_init (TYPE_1__*,int) ; 
 int strlen (int*) ; 

int nn_create_socket (nn_options_t *options)
{
    int sock;
    int rc;
    int millis;

    sock = nn_socket (AF_SP, options->socket_type);
    nn_assert_errno (sock >= 0, "Can't create socket");

    /* Generic initialization */
    if (options->send_timeout >= 0) {
        millis = (int)(options->send_timeout * 1000);
        rc = nn_setsockopt (sock, NN_SOL_SOCKET, NN_SNDTIMEO,
                           &millis, sizeof (millis));
        nn_assert_errno (rc == 0, "Can't set send timeout");
    }
    if (options->recv_timeout >= 0) {
        nn_set_recv_timeout (sock, (int) options->recv_timeout * 1000);
    }
    if (options->socket_name) {
        rc = nn_setsockopt (sock, NN_SOL_SOCKET, NN_SOCKET_NAME,
                           options->socket_name, strlen(options->socket_name));
        nn_assert_errno (rc == 0, "Can't set socket name");
    }

    /* Specific initialization */
    switch (options->socket_type) {
    case NN_SUB:
        nn_sub_init (options, sock);
        break;
    }

    return sock;
}