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
struct atmel_ssc_info {int daifmt; } ;

/* Variables and functions */
#define  SND_SOC_DAIFMT_CBS_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 int SND_SOC_DAIFMT_MASTER_MASK ; 

__attribute__((used)) static int atmel_ssc_cbs(struct atmel_ssc_info *ssc_p)
{
	switch (ssc_p->daifmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFM:
	case SND_SOC_DAIFMT_CBS_CFS:
		return 1;
	}
	return 0;
}