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
struct nlm_host {struct net* net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockd_down (struct net*) ; 
 int /*<<< orphan*/  nlmclnt_release_host (struct nlm_host*) ; 

void nlmclnt_done(struct nlm_host *host)
{
	struct net *net = host->net;

	nlmclnt_release_host(host);
	lockd_down(net);
}