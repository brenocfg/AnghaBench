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
struct halmac_adapter {int gen_info_valid; scalar_t__ h2c_buf_free_space; scalar_t__ h2c_packet_seq; } ;

/* Variables and functions */

void halmac_init_adapter_dynamic_para_88xx(
	struct halmac_adapter *halmac_adapter)
{
	halmac_adapter->h2c_packet_seq = 0;
	halmac_adapter->h2c_buf_free_space = 0;
	halmac_adapter->gen_info_valid = false;
}