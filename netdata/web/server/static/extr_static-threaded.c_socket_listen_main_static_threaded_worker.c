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
struct web_server_static_threaded_worker {int running; int /*<<< orphan*/  max_sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/  api_sockets ; 
 int default_rrd_update_every ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  poll_events (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_listen_main_static_threaded_worker_cleanup ; 
 int /*<<< orphan*/  web_allow_connections_dns ; 
 int /*<<< orphan*/  web_allow_connections_from ; 
 int /*<<< orphan*/  web_client_first_request_timeout ; 
 int /*<<< orphan*/  web_client_timeout ; 
 int /*<<< orphan*/  web_server_add_callback ; 
 int /*<<< orphan*/  web_server_del_callback ; 
 int /*<<< orphan*/  web_server_rcv_callback ; 
 int /*<<< orphan*/  web_server_snd_callback ; 
 int /*<<< orphan*/  web_server_tmr_callback ; 
 struct web_server_static_threaded_worker* worker_private ; 

void *socket_listen_main_static_threaded_worker(void *ptr) {
    worker_private = (struct web_server_static_threaded_worker *)ptr;
    worker_private->running = 1;

    netdata_thread_cleanup_push(socket_listen_main_static_threaded_worker_cleanup, ptr);

            poll_events(&api_sockets
                        , web_server_add_callback
                        , web_server_del_callback
                        , web_server_rcv_callback
                        , web_server_snd_callback
                        , web_server_tmr_callback
                        , web_allow_connections_from
                        , web_allow_connections_dns
                        , NULL
                        , web_client_first_request_timeout
                        , web_client_timeout
                        , default_rrd_update_every * 1000 // timer_milliseconds
                        , ptr // timer_data
                        , worker_private->max_sockets
            );

    netdata_thread_cleanup_pop(1);
    return NULL;
}