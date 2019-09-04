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
struct knav_dma_desc {int /*<<< orphan*/  next_desc; int /*<<< orphan*/  buff; int /*<<< orphan*/  buff_len; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_pkt_info(dma_addr_t *buff, u32 *buff_len, dma_addr_t *ndesc,
			 struct knav_dma_desc *desc)
{
	*buff_len = le32_to_cpu(desc->buff_len);
	*buff = le32_to_cpu(desc->buff);
	*ndesc = le32_to_cpu(desc->next_desc);
}