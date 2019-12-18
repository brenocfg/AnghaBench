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
typedef  int u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SDnFMT_BASE (int) ; 
 int SDnFMT_DIV (int) ; 
 int SDnFMT_MULT (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline u32 get_mult_div(struct snd_sof_dev *sdev, int rate)
{
	switch (rate) {
	case 8000:
		return SDnFMT_DIV(6);
	case 9600:
		return SDnFMT_DIV(5);
	case 11025:
		return SDnFMT_BASE(1) | SDnFMT_DIV(4);
	case 16000:
		return SDnFMT_DIV(3);
	case 22050:
		return SDnFMT_BASE(1) | SDnFMT_DIV(2);
	case 32000:
		return SDnFMT_DIV(3) | SDnFMT_MULT(2);
	case 44100:
		return SDnFMT_BASE(1);
	case 48000:
		return 0;
	case 88200:
		return SDnFMT_BASE(1) | SDnFMT_MULT(2);
	case 96000:
		return SDnFMT_MULT(2);
	case 176400:
		return SDnFMT_BASE(1) | SDnFMT_MULT(4);
	case 192000:
		return SDnFMT_MULT(4);
	default:
		dev_warn(sdev->dev, "can't find div rate %d using 48kHz\n",
			 rate);
		return 0; /* use 48KHz if not found */
	}
}