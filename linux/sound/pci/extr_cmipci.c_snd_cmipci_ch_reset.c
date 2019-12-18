#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cmipci {int ctrl; TYPE_1__* channel; } ;
struct TYPE_2__ {int ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_REG_FUNCTRL0 ; 
 int CM_RST_CH0 ; 
 int /*<<< orphan*/  snd_cmipci_write (struct cmipci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_cmipci_ch_reset(struct cmipci *cm, int ch)
{
	int reset = CM_RST_CH0 << (cm->channel[ch].ch);
	snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl | reset);
	snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl & ~reset);
	udelay(10);
}