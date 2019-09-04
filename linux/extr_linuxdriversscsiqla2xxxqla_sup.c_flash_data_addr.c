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
typedef  int uint32_t ;
struct qla_hw_data {int flash_data_off; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
flash_data_addr(struct qla_hw_data *ha, uint32_t faddr)
{
	return ha->flash_data_off | faddr;
}