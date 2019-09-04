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
struct smbd_negotiate_resp {int /*<<< orphan*/  max_fragmented_size; int /*<<< orphan*/  max_receive_size; int /*<<< orphan*/  preferred_send_size; int /*<<< orphan*/  max_readwrite_size; int /*<<< orphan*/  status; int /*<<< orphan*/  credits_granted; int /*<<< orphan*/  credits_requested; int /*<<< orphan*/  negotiated_version; int /*<<< orphan*/  max_version; int /*<<< orphan*/  min_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  log_rdma_event (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_smbd_negotiate_resp(struct smbd_negotiate_resp *resp)
{
	log_rdma_event(INFO, "resp message min_version %u max_version %u "
		"negotiated_version %u credits_requested %u "
		"credits_granted %u status %u max_readwrite_size %u "
		"preferred_send_size %u max_receive_size %u "
		"max_fragmented_size %u\n",
		resp->min_version, resp->max_version, resp->negotiated_version,
		resp->credits_requested, resp->credits_granted, resp->status,
		resp->max_readwrite_size, resp->preferred_send_size,
		resp->max_receive_size, resp->max_fragmented_size);
}