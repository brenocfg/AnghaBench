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
struct web_client {int /*<<< orphan*/  client_port; int /*<<< orphan*/  client_ip; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettid () ; 
 int /*<<< orphan*/  log_access (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void web_server_log_connection(struct web_client *w, const char *msg) {
    log_access("%llu: %d '[%s]:%s' '%s'", w->id, gettid(), w->client_ip, w->client_port, msg);
}