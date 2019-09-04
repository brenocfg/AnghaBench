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
struct msdc_host {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MSDC_CFG ; 
 int MSDC_CFG_RST ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sdr_set_bits (scalar_t__,int) ; 

__attribute__((used)) static void msdc_reset_hw(struct msdc_host *host)
{
	sdr_set_bits(host->base + MSDC_CFG, MSDC_CFG_RST);
	while (readl(host->base + MSDC_CFG) & MSDC_CFG_RST)
		cpu_relax();
}