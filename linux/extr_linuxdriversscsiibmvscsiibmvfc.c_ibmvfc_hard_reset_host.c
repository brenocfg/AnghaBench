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
struct ibmvfc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_RESET ; 
 int /*<<< orphan*/  IBMVFC_LINK_DOWN ; 
 int /*<<< orphan*/  ibmvfc_link_down (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_purge_requests (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_host_action (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvfc_hard_reset_host(struct ibmvfc_host *vhost)
{
	ibmvfc_purge_requests(vhost, DID_ERROR);
	ibmvfc_link_down(vhost, IBMVFC_LINK_DOWN);
	ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_RESET);
}