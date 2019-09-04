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
typedef  size_t uint32_t ;
struct tcmu_cmd {int dummy; } ;

/* Variables and functions */
 size_t DATA_BLOCK_SIZE ; 
 size_t tcmu_cmd_get_data_length (struct tcmu_cmd*) ; 

__attribute__((used)) static inline uint32_t tcmu_cmd_get_block_cnt(struct tcmu_cmd *tcmu_cmd)
{
	size_t data_length = tcmu_cmd_get_data_length(tcmu_cmd);

	return data_length / DATA_BLOCK_SIZE;
}