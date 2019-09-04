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
struct snic_fw_req {int dummy; } ;
struct snic {int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_ASSERT_NOT_IMPL (int) ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
snic_msg_ack_handler(struct snic *snic, struct snic_fw_req *fwreq)
{
	SNIC_HOST_INFO(snic->shost, "Message Ack Received.\n");

	SNIC_ASSERT_NOT_IMPL(1);
}