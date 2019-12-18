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
struct nn_sock {char* socket_name; } ;
struct nn_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 char* nn_ep_getaddr (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_global_print_errors () ; 
 char* nn_strerror (int) ; 
 int /*<<< orphan*/  stderr ; 

void nn_sock_report_error (struct nn_sock *self, struct nn_ep *ep, int errnum)
{
    if (!nn_global_print_errors())
        return;

    if (errnum == 0)
        return;

    if (ep) {
        fprintf(stderr, "nanomsg: socket.%s[%s]: Error: %s\n",
            self->socket_name, nn_ep_getaddr(ep), nn_strerror(errnum));
    } else {
        fprintf(stderr, "nanomsg: socket.%s: Error: %s\n",
            self->socket_name, nn_strerror(errnum));
    }
}