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
typedef  int u32 ;
struct snd_cs46xx {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_SERBST ; 
 int EINVAL ; 
 int SERBST_WBSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs46xx_wait_for_fifo(struct snd_cs46xx * chip,int retry_timeout) 
{
	u32 i, status = 0;
	/*
	 * Make sure the previous FIFO write operation has completed.
	 */
	for(i = 0; i < 50; i++){
		status = snd_cs46xx_peekBA0(chip, BA0_SERBST);
    
		if( !(status & SERBST_WBSY) )
			break;

		mdelay(retry_timeout);
	}
  
	if(status & SERBST_WBSY) {
		dev_err(chip->card->dev,
			"failure waiting for FIFO command to complete\n");
		return -EINVAL;
	}

	return 0;
}