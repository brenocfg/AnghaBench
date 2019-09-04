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
struct TYPE_2__ {int rt; } ;
struct rt2x00_dev {TYPE_1__ chip; } ;

/* Variables and functions */
#define  RT3593 130 
#define  RT5592 129 
#define  RT6352 128 
 unsigned short RXWI_DESC_SIZE_4WORDS ; 
 unsigned short RXWI_DESC_SIZE_5WORDS ; 
 unsigned short RXWI_DESC_SIZE_6WORDS ; 
 unsigned short TXWI_DESC_SIZE_4WORDS ; 
 unsigned short TXWI_DESC_SIZE_5WORDS ; 

void rt2800_get_txwi_rxwi_size(struct rt2x00_dev *rt2x00dev,
			       unsigned short *txwi_size,
			       unsigned short *rxwi_size)
{
	switch (rt2x00dev->chip.rt) {
	case RT3593:
		*txwi_size = TXWI_DESC_SIZE_4WORDS;
		*rxwi_size = RXWI_DESC_SIZE_5WORDS;
		break;

	case RT5592:
	case RT6352:
		*txwi_size = TXWI_DESC_SIZE_5WORDS;
		*rxwi_size = RXWI_DESC_SIZE_6WORDS;
		break;

	default:
		*txwi_size = TXWI_DESC_SIZE_4WORDS;
		*rxwi_size = RXWI_DESC_SIZE_4WORDS;
		break;
	}
}