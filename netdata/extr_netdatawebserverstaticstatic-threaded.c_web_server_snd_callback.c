#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct web_client {int ifd; int ofd; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  sends; } ;
struct TYPE_4__ {int fd; scalar_t__ data; } ;
typedef  TYPE_1__ POLLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 short POLLIN ; 
 short POLLOUT ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ web_client_has_wait_receive (struct web_client*) ; 
 scalar_t__ web_client_has_wait_send (struct web_client*) ; 
 scalar_t__ web_client_send (struct web_client*) ; 
 int web_server_check_client_status (struct web_client*) ; 
 TYPE_2__* worker_private ; 

__attribute__((used)) static int web_server_snd_callback(POLLINFO *pi, short int *events) {
    worker_private->sends++;

    struct web_client *w = (struct web_client *)pi->data;
    int fd = pi->fd;

    debug(D_WEB_CLIENT, "%llu: sending data on fd %d.", w->id, fd);

    if(unlikely(web_client_send(w) < 0))
        return -1;

    if(unlikely(w->ifd == fd && web_client_has_wait_receive(w)))
        *events |= POLLIN;

    if(unlikely(w->ofd == fd && web_client_has_wait_send(w)))
        *events |= POLLOUT;

    return web_server_check_client_status(w);
}