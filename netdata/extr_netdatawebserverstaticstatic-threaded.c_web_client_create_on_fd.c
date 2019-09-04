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
struct web_client {int ifd; int ofd; int port_acl; int /*<<< orphan*/ * client_port; int /*<<< orphan*/ * client_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ unlikely (int) ; 
 struct web_client* web_client_get_from_cache_or_allocate () ; 
 int /*<<< orphan*/  web_client_initialize_connection (struct web_client*) ; 

__attribute__((used)) static struct web_client *web_client_create_on_fd(int fd, const char *client_ip, const char *client_port, int port_acl) {
    struct web_client *w;

    w = web_client_get_from_cache_or_allocate();
    w->ifd = w->ofd = fd;

    strncpyz(w->client_ip, client_ip, sizeof(w->client_ip) - 1);
    strncpyz(w->client_port, client_port, sizeof(w->client_port) - 1);

    if(unlikely(!*w->client_ip))   strcpy(w->client_ip,   "-");
    if(unlikely(!*w->client_port)) strcpy(w->client_port, "-");
	w->port_acl = port_acl;

    web_client_initialize_connection(w);
    return(w);
}