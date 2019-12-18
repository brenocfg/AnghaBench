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
struct TYPE_2__ {scalar_t__ conn; int /*<<< orphan*/  flags; } ;
struct web_client {int /*<<< orphan*/  ofd; TYPE_1__ ssl; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_write (scalar_t__,void const*,size_t) ; 
 scalar_t__ netdata_srv_ctx ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,void const*,size_t,int) ; 
 int /*<<< orphan*/  web_client_check_unix (struct web_client*) ; 

__attribute__((used)) static inline ssize_t web_client_send_data(struct web_client *w,const void *buf,size_t len, int flags)
{
    ssize_t bytes;
#ifdef ENABLE_HTTPS
    if ( (!web_client_check_unix(w)) && (netdata_srv_ctx) ) {
        if ( ( w->ssl.conn ) && ( !w->ssl.flags ) ){
            bytes = SSL_write(w->ssl.conn,buf, len) ;
        } else {
            bytes = send(w->ofd,buf, len , flags);
        }
    } else {
        bytes = send(w->ofd,buf, len , flags);
    }
#else
    bytes = send(w->ofd, buf, len, flags);
#endif

    return bytes;
}