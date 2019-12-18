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

/* Variables and functions */
 int GCR ; 
 int GCR_CDONE_IE ; 
 int GCR_PRIRDY_IEN ; 
 int GCR_SDONE_IE ; 
 int GCR_SECRDY_IEN ; 

void pxa2xx_ac97_finish_reset(void)
{
	GCR &= ~(GCR_PRIRDY_IEN|GCR_SECRDY_IEN);
	GCR |= GCR_SDONE_IE|GCR_CDONE_IE;
}