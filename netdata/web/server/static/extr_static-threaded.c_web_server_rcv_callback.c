#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct web_client {scalar_t__ mode; scalar_t__ pollinfo_filecopy_slot; int ifd; int ofd; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  receptions; } ;
struct TYPE_5__ {int fd; scalar_t__ slot; int /*<<< orphan*/  port_acl; int /*<<< orphan*/  p; scalar_t__ data; } ;
typedef  TYPE_1__ POLLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 short POLLIN ; 
 int /*<<< orphan*/  POLLINFO_FLAG_CLIENT_SOCKET ; 
 short POLLOUT ; 
 scalar_t__ WEB_CLIENT_MODE_FILECOPY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__* poll_add_fd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ web_client_has_wait_receive (struct web_client*) ; 
 scalar_t__ web_client_has_wait_send (struct web_client*) ; 
 int /*<<< orphan*/  web_client_process_request (struct web_client*) ; 
 scalar_t__ web_client_receive (struct web_client*) ; 
 int web_server_check_client_status (struct web_client*) ; 
 int /*<<< orphan*/  web_server_file_add_callback ; 
 int /*<<< orphan*/  web_server_file_del_callback ; 
 int /*<<< orphan*/  web_server_file_read_callback ; 
 int /*<<< orphan*/  web_server_file_write_callback ; 
 TYPE_2__* worker_private ; 

__attribute__((used)) static int web_server_rcv_callback(POLLINFO *pi, short int *events) {
    worker_private->receptions++;

    struct web_client *w = (struct web_client *)pi->data;
    int fd = pi->fd;

    //BRING IT TO HERE

    if(unlikely(web_client_receive(w) < 0))
        return -1;

    debug(D_WEB_CLIENT, "%llu: processing received data on fd %d.", w->id, fd);
    web_client_process_request(w);

    if(unlikely(w->mode == WEB_CLIENT_MODE_FILECOPY)) {
        if(w->pollinfo_filecopy_slot == 0) {
            debug(D_WEB_CLIENT, "%llu: FILECOPY DETECTED ON FD %d", w->id, pi->fd);

            if (unlikely(w->ifd != -1 && w->ifd != w->ofd && w->ifd != fd)) {
                // add a new socket to poll_events, with the same
                debug(D_WEB_CLIENT, "%llu: CREATING FILECOPY SLOT ON FD %d", w->id, pi->fd);

                POLLINFO *fpi = poll_add_fd(
                        pi->p
                        , w->ifd
                        , pi->port_acl
                        , 0
                        , POLLINFO_FLAG_CLIENT_SOCKET
                        , "FILENAME"
                        , ""
                        , ""
                        , web_server_file_add_callback
                        , web_server_file_del_callback
                        , web_server_file_read_callback
                        , web_server_file_write_callback
                        , (void *) w
                );

                if(fpi)
                    w->pollinfo_filecopy_slot = fpi->slot;
                else {
                    error("Failed to add filecopy fd. Closing client.");
                    return -1;
                }
            }
        }
    }
    else {
        if(unlikely(w->ifd == fd && web_client_has_wait_receive(w)))
            *events |= POLLIN;
    }

    if(unlikely(w->ofd == fd && web_client_has_wait_send(w)))
        *events |= POLLOUT;

    return web_server_check_client_status(w);
}