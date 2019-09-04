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
typedef  int uint ;
struct mpsc_port_info {scalar_t__ sdma_base; } ;

/* Variables and functions */
 scalar_t__ SDMA_SDCM ; 
 int SDMA_SDCM_TXD ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static uint mpsc_sdma_tx_active(struct mpsc_port_info *pi)
{
	return readl(pi->sdma_base + SDMA_SDCM) & SDMA_SDCM_TXD;
}