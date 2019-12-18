#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct web_client {int /*<<< orphan*/  pollinfo_slot; int /*<<< orphan*/  port_acl; int /*<<< orphan*/ * client_port; int /*<<< orphan*/ * client_ip; int /*<<< orphan*/ * client_host; int /*<<< orphan*/  ofd; int /*<<< orphan*/  ifd; } ;
struct TYPE_3__ {int /*<<< orphan*/  slot; int /*<<< orphan*/  port_acl; int /*<<< orphan*/  client_host; int /*<<< orphan*/  client_port; int /*<<< orphan*/  client_ip; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ POLLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 struct web_client* web_client_get_from_cache_or_allocate () ; 
 int /*<<< orphan*/  web_client_initialize_connection (struct web_client*) ; 

__attribute__((used)) static struct web_client *web_client_create_on_fd(POLLINFO *pi) {
    struct web_client *w;

    w = web_client_get_from_cache_or_allocate();
    w->ifd = w->ofd = pi->fd;

    strncpyz(w->client_ip,   pi->client_ip,   sizeof(w->client_ip) - 1);
    strncpyz(w->client_port, pi->client_port, sizeof(w->client_port) - 1);
    strncpyz(w->client_host, pi->client_host, sizeof(w->client_host) - 1);

    if(unlikely(!*w->client_ip))   strcpy(w->client_ip,   "-");
    if(unlikely(!*w->client_port)) strcpy(w->client_port, "-");
	w->port_acl = pi->port_acl;

    web_client_initialize_connection(w);
    w->pollinfo_slot = pi->slot;
    return(w);
}