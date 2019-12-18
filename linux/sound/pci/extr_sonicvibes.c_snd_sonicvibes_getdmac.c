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
struct sonicvibes {scalar_t__ dmac_port; } ;

/* Variables and functions */
 scalar_t__ SV_DMA_COUNT0 ; 
 int inl (scalar_t__) ; 

__attribute__((used)) static inline unsigned int snd_sonicvibes_getdmac(struct sonicvibes * sonic)
{
	/* note: dmac is working in word mode!!! */
	return ((inl(sonic->dmac_port + SV_DMA_COUNT0) & 0xffffff) + 1) << 1;
}