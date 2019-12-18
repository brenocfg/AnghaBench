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
struct ceph_client {int /*<<< orphan*/  osdc; int /*<<< orphan*/  monc; int /*<<< orphan*/  msgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_messenger_reset_nonce (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_monc_reopen_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_osdc_reopen_osds (int /*<<< orphan*/ *) ; 

void ceph_reset_client_addr(struct ceph_client *client)
{
	ceph_messenger_reset_nonce(&client->msgr);
	ceph_monc_reopen_session(&client->monc);
	ceph_osdc_reopen_osds(&client->osdc);
}