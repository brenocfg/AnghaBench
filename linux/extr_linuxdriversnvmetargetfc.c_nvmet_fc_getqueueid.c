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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int NVMET_FC_QUEUEID_MASK ; 

__attribute__((used)) static inline u16
nvmet_fc_getqueueid(u64 connectionid)
{
	return (u16)(connectionid & NVMET_FC_QUEUEID_MASK);
}