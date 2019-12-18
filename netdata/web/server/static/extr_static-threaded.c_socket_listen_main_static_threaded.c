#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct web_server_static_threaded_worker {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  opened; } ;
struct TYPE_6__ {int rlim_cur; } ;
struct TYPE_5__ {int id; size_t max_sockets; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_WEB ; 
 int /*<<< orphan*/  NETDATA_SSL_CONTEXT_SERVER ; 
 int /*<<< orphan*/  NETDATA_THREAD_OPTION_DEFAULT ; 
 int /*<<< orphan*/  WEB_SERVER_MODE_STATIC_THREADED ; 
 TYPE_4__ api_sockets ; 
 TYPE_1__* callocz (size_t,int) ; 
 int /*<<< orphan*/  config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int config_get_number (int /*<<< orphan*/ ,char*,long long) ; 
 int /*<<< orphan*/  config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  netdata_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),void*) ; 
 int processors ; 
 TYPE_2__ rlimit_nofile ; 
 int /*<<< orphan*/  security_start_ssl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,int) ; 
 int /*<<< orphan*/  socket_listen_main_static_threaded_cleanup ; 
 int /*<<< orphan*/  socket_listen_main_static_threaded_worker (void*) ; 
 int static_threaded_workers_count ; 
 TYPE_1__* static_workers_private_data ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int web_server_is_multithreaded ; 
 int /*<<< orphan*/  web_server_mode ; 

void *socket_listen_main_static_threaded(void *ptr) {
    netdata_thread_cleanup_push(socket_listen_main_static_threaded_cleanup, ptr);
            web_server_mode = WEB_SERVER_MODE_STATIC_THREADED;

            if(!api_sockets.opened)
                fatal("LISTENER: no listen sockets available.");

#ifdef ENABLE_HTTPS
            security_start_ssl(NETDATA_SSL_CONTEXT_SERVER);
#endif
            // 6 threads is the optimal value
            // since 6 are the parallel connections browsers will do
            // so, if the machine has more CPUs, avoid using resources unnecessarily
            int def_thread_count = (processors > 6)?6:processors;

            if (!strcmp(config_get(CONFIG_SECTION_WEB, "mode", ""),"single-threaded")) {
                info("Running web server with one thread, because mode is single-threaded");
                config_set(CONFIG_SECTION_WEB, "mode", "static-threaded");
                def_thread_count = 1;
            }
            static_threaded_workers_count = config_get_number(CONFIG_SECTION_WEB, "web server threads", def_thread_count);

            if(static_threaded_workers_count < 1) static_threaded_workers_count = 1;

            size_t max_sockets = (size_t)config_get_number(CONFIG_SECTION_WEB, "web server max sockets", (long long int)(rlimit_nofile.rlim_cur / 4));

            static_workers_private_data = callocz((size_t)static_threaded_workers_count, sizeof(struct web_server_static_threaded_worker));

            web_server_is_multithreaded = (static_threaded_workers_count > 1);

            int i;
            for(i = 1; i < static_threaded_workers_count; i++) {
                static_workers_private_data[i].id = i;
                static_workers_private_data[i].max_sockets = max_sockets / static_threaded_workers_count;

                char tag[50 + 1];
                snprintfz(tag, 50, "WEB_SERVER[static%d]", i+1);

                info("starting worker %d", i+1);
                netdata_thread_create(&static_workers_private_data[i].thread, tag, NETDATA_THREAD_OPTION_DEFAULT, socket_listen_main_static_threaded_worker, (void *)&static_workers_private_data[i]);
            }

            // and the main one
            static_workers_private_data[0].max_sockets = max_sockets / static_threaded_workers_count;
            socket_listen_main_static_threaded_worker((void *)&static_workers_private_data[0]);

    netdata_thread_cleanup_pop(1);
    return NULL;
}