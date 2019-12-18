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
struct nsm_handle {int dummy; } ;
struct nlm_reboot {int dummy; } ;
struct nlm_host {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nlm_host* next_host_state (int /*<<< orphan*/ ,struct nsm_handle*,struct nlm_reboot const*) ; 
 int /*<<< orphan*/  nlm_client_hosts ; 
 int /*<<< orphan*/  nlm_server_hosts ; 
 int /*<<< orphan*/  nlmclnt_recovery (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmclnt_release_host (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmsvc_free_host_resources (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmsvc_release_host (struct nlm_host*) ; 
 struct nsm_handle* nsm_reboot_lookup (struct net const*,struct nlm_reboot const*) ; 
 int /*<<< orphan*/  nsm_release (struct nsm_handle*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void nlm_host_rebooted(const struct net *net, const struct nlm_reboot *info)
{
	struct nsm_handle *nsm;
	struct nlm_host	*host;

	nsm = nsm_reboot_lookup(net, info);
	if (unlikely(nsm == NULL))
		return;

	/* Mark all hosts tied to this NSM state as having rebooted.
	 * We run the loop repeatedly, because we drop the host table
	 * lock for this.
	 * To avoid processing a host several times, we match the nsmstate.
	 */
	while ((host = next_host_state(nlm_server_hosts, nsm, info)) != NULL) {
		nlmsvc_free_host_resources(host);
		nlmsvc_release_host(host);
	}
	while ((host = next_host_state(nlm_client_hosts, nsm, info)) != NULL) {
		nlmclnt_recovery(host);
		nlmclnt_release_host(host);
	}

	nsm_release(nsm);
}