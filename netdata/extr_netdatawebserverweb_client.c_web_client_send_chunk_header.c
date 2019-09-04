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
struct web_client {int /*<<< orphan*/  id; int /*<<< orphan*/  stats_sent_bytes; int /*<<< orphan*/  ofd; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_DEFLATE ; 
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int /*<<< orphan*/  WEB_CLIENT_IS_DEAD (struct web_client*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlen (char*) ; 

ssize_t web_client_send_chunk_header(struct web_client *w, size_t len)
{
    debug(D_DEFLATE, "%llu: OPEN CHUNK of %zu bytes (hex: %zx).", w->id, len, len);
    char buf[24];
    sprintf(buf, "%zX\r\n", len);
    
    ssize_t bytes = send(w->ofd, buf, strlen(buf), 0);
    if(bytes > 0) {
        debug(D_DEFLATE, "%llu: Sent chunk header %zd bytes.", w->id, bytes);
        w->stats_sent_bytes += bytes;
    }

    else if(bytes == 0) {
        debug(D_WEB_CLIENT, "%llu: Did not send chunk header to the client.", w->id);
        WEB_CLIENT_IS_DEAD(w);
    }
    else {
        debug(D_WEB_CLIENT, "%llu: Failed to send chunk header to client.", w->id);
        WEB_CLIENT_IS_DEAD(w);
    }

    return bytes;
}