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
struct TYPE_2__ {scalar_t__ os_type; } ;
struct scsi_info {TYPE_1__ client_data; scalar_t__ client_cap; } ;

/* Variables and functions */

__attribute__((used)) static void ibmvscsis_delete_client_info(struct scsi_info *vscsi,
					 bool client_closed)
{
	vscsi->client_cap = 0;

	/*
	 * Some things we don't want to clear if we're closing the queue,
	 * because some clients don't resend the host handshake when they
	 * get a transport event.
	 */
	if (client_closed)
		vscsi->client_data.os_type = 0;
}