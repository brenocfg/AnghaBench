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
typedef  int u32 ;
struct netvsc_device {scalar_t__ nvsp_version; int recv_section_size; int send_section_size; int /*<<< orphan*/  send_section_cnt; int /*<<< orphan*/  recv_section_cnt; } ;
struct ethtool_ringparam {int rx_max_pending; int tx_max_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; } ;

/* Variables and functions */
 int NETVSC_RECEIVE_BUFFER_SIZE ; 
 int NETVSC_RECEIVE_BUFFER_SIZE_LEGACY ; 
 int NETVSC_SEND_BUFFER_SIZE ; 
 scalar_t__ NVSP_PROTOCOL_VERSION_2 ; 

__attribute__((used)) static void __netvsc_get_ringparam(struct netvsc_device *nvdev,
				   struct ethtool_ringparam *ring)
{
	u32 max_buf_size;

	ring->rx_pending = nvdev->recv_section_cnt;
	ring->tx_pending = nvdev->send_section_cnt;

	if (nvdev->nvsp_version <= NVSP_PROTOCOL_VERSION_2)
		max_buf_size = NETVSC_RECEIVE_BUFFER_SIZE_LEGACY;
	else
		max_buf_size = NETVSC_RECEIVE_BUFFER_SIZE;

	ring->rx_max_pending = max_buf_size / nvdev->recv_section_size;
	ring->tx_max_pending = NETVSC_SEND_BUFFER_SIZE
		/ nvdev->send_section_size;
}