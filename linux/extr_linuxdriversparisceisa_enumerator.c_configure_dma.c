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
typedef  int u_int8_t ;

/* Variables and functions */
 int HPEE_DMA_CHANNEL_MASK ; 
 int HPEE_DMA_MAX_ENT ; 
 int HPEE_DMA_MORE ; 
 int get_8 (unsigned char const*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static int configure_dma(const unsigned char *buf)
{
	int len;
	u_int8_t c;
	int i;
	
	len=0;
	
	for (i=0;i<HPEE_DMA_MAX_ENT;i++) {
		c = get_8(buf+len);
		printk("DMA %d ", c&HPEE_DMA_CHANNEL_MASK);
		/* fixme: maybe initialize the dma channel withthe timing ? */
		len+=2;      
		if (!(c & HPEE_DMA_MORE)) {
			break;
		}
	}
	
	return len;
}