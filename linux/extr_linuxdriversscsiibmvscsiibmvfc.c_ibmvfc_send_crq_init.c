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
 int /*<<< orphan*/  ibmvfc_dbg (struct ibmvfc_host*,char*) ; 
 int ibmvfc_send_crq (struct ibmvfc_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvfc_send_crq_init(struct ibmvfc_host *vhost)
{
	ibmvfc_dbg(vhost, "Sending CRQ init\n");
	return ibmvfc_send_crq(vhost, 0xC001000000000000LL, 0);
}