#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dma16; int dma8; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ SB16 ;

/* Variables and functions */
 int /*<<< orphan*/  MIXER_DMA_SETUP_REGISTER ; 
 unsigned char read_mixer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void get_dma(SB16* sb16)
{
	unsigned char hi,lo,result=read_mixer(sb16->base,MIXER_DMA_SETUP_REGISTER);
  hi=result&0xE0;
  lo=result&0x0B;
  if(hi==0x80) sb16->dma16=7;
  if(hi==0x40) sb16->dma16=6;
  if(hi==0x20) sb16->dma16=5;

  if(lo==0x08) sb16->dma8=3;
  if(lo==0x02) sb16->dma8=1;
  if(lo==0x01) sb16->dma8=0;
}