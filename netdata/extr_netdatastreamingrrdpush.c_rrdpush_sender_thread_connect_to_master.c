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
struct timeval {int tv_sec; int /*<<< orphan*/  tv_usec; } ;
struct TYPE_4__ {char* rrdpush_send_destination; int rrdpush_sender_socket; char* tags; int /*<<< orphan*/  hostname; int /*<<< orphan*/  program_version; int /*<<< orphan*/  program_name; int /*<<< orphan*/  timezone; int /*<<< orphan*/  os; int /*<<< orphan*/  machine_guid; int /*<<< orphan*/  registry_hostname; int /*<<< orphan*/  rrdpush_send_api_key; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 char* START_STREAMING_PROMPT ; 
 int connect_to_one_of (char*,int,struct timeval*,size_t*,char*,size_t) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  default_rrd_update_every ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,char*) ; 
 int recv_timeout (int,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rrdpush_sender_thread_close_socket (TYPE_1__*) ; 
 int send_timeout (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_enlarge_out (int) ; 
 scalar_t__ sock_setnonblock (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rrdpush_sender_thread_connect_to_master(RRDHOST *host, int default_port, int timeout, size_t *reconnects_counter, char *connected_to, size_t connected_to_size) {
    struct timeval tv = {
            .tv_sec = timeout,
            .tv_usec = 0
    };

    // make sure the socket is closed
    rrdpush_sender_thread_close_socket(host);

    debug(D_STREAM, "STREAM: Attempting to connect...");
    info("STREAM %s [send to %s]: connecting...", host->hostname, host->rrdpush_send_destination);

    host->rrdpush_sender_socket = connect_to_one_of(
            host->rrdpush_send_destination
            , default_port
            , &tv
            , reconnects_counter
            , connected_to
            , connected_to_size
    );

    if(unlikely(host->rrdpush_sender_socket == -1)) {
        error("STREAM %s [send to %s]: failed to connect", host->hostname, host->rrdpush_send_destination);
        return 0;
    }

    info("STREAM %s [send to %s]: initializing communication...", host->hostname, connected_to);

    #define HTTP_HEADER_SIZE 8192
    char http[HTTP_HEADER_SIZE + 1];
    snprintfz(http, HTTP_HEADER_SIZE,
            "STREAM key=%s&hostname=%s&registry_hostname=%s&machine_guid=%s&update_every=%d&os=%s&timezone=%s&tags=%s HTTP/1.1\r\n"
                    "User-Agent: %s/%s\r\n"
                    "Accept: */*\r\n\r\n"
              , host->rrdpush_send_api_key
              , host->hostname
              , host->registry_hostname
              , host->machine_guid
              , default_rrd_update_every
              , host->os
              , host->timezone
              , (host->tags)?host->tags:""
              , host->program_name
              , host->program_version
    );

    if(send_timeout(host->rrdpush_sender_socket, http, strlen(http), 0, timeout) == -1) {
        error("STREAM %s [send to %s]: failed to send HTTP header to remote netdata.", host->hostname, connected_to);
        rrdpush_sender_thread_close_socket(host);
        return 0;
    }

    info("STREAM %s [send to %s]: waiting response from remote netdata...", host->hostname, connected_to);

    if(recv_timeout(host->rrdpush_sender_socket, http, HTTP_HEADER_SIZE, 0, timeout) == -1) {
        error("STREAM %s [send to %s]: remote netdata does not respond.", host->hostname, connected_to);
        rrdpush_sender_thread_close_socket(host);
        return 0;
    }

    if(strncmp(http, START_STREAMING_PROMPT, strlen(START_STREAMING_PROMPT)) != 0) {
        error("STREAM %s [send to %s]: server is not replying properly (is it a netdata?).", host->hostname, connected_to);
        rrdpush_sender_thread_close_socket(host);
        return 0;
    }

    info("STREAM %s [send to %s]: established communication - ready to send metrics...", host->hostname, connected_to);

    if(sock_setnonblock(host->rrdpush_sender_socket) < 0)
        error("STREAM %s [send to %s]: cannot set non-blocking mode for socket.", host->hostname, connected_to);

    if(sock_enlarge_out(host->rrdpush_sender_socket) < 0)
        error("STREAM %s [send to %s]: cannot enlarge the socket buffer.", host->hostname, connected_to);

    debug(D_STREAM, "STREAM: Connected on fd %d...", host->rrdpush_sender_socket);

    return 1;
}