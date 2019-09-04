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
struct fpm_worker_pool_s {scalar_t__ listen_address_domain; TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  listen_allowed_clients; } ;

/* Variables and functions */
 scalar_t__ FPM_AF_INET ; 
 int /*<<< orphan*/  fcgi_set_allowed_clients (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fpm_php_set_allowed_clients(struct fpm_worker_pool_s *wp) /* {{{ */
{
	if (wp->listen_address_domain == FPM_AF_INET) {
		fcgi_set_allowed_clients(wp->config->listen_allowed_clients);
	}
	return 0;
}