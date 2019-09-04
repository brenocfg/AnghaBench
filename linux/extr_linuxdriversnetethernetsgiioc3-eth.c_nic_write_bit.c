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
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc3_w_mcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcr_pack (int,int) ; 
 int /*<<< orphan*/  nic_wait (struct ioc3*) ; 

__attribute__((used)) static inline void nic_write_bit(struct ioc3 *ioc3, int bit)
{
	if (bit)
		ioc3_w_mcr(mcr_pack(6, 110));
	else
		ioc3_w_mcr(mcr_pack(80, 30));

	nic_wait(ioc3);
}