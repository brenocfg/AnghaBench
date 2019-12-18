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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9XXX_A_CDC_CLSH_CRC ; 
 int WCD9XXX_A_CDC_CLSH_CRC_CLK_EN_MASK ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool wcd_clsh_enable_status(struct snd_soc_component *comp)
{
	return snd_soc_component_read32(comp, WCD9XXX_A_CDC_CLSH_CRC) &
					WCD9XXX_A_CDC_CLSH_CRC_CLK_EN_MASK;
}