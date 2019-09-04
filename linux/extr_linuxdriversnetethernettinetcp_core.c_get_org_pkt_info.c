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
typedef  void* u32 ;
struct knav_dma_desc {int /*<<< orphan*/  orig_len; int /*<<< orphan*/  orig_buff; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_org_pkt_info(dma_addr_t *buff, u32 *buff_len,
			     struct knav_dma_desc *desc)
{
	*buff = le32_to_cpu(desc->orig_buff);
	*buff_len = le32_to_cpu(desc->orig_len);
}