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
struct rtd_boardinfo {unsigned int range_bip10; unsigned int range_uni10; } ;
struct comedi_device {struct rtd_boardinfo* board_ptr; } ;

/* Variables and functions */
#define  AREF_COMMON 131 
#define  AREF_DIFF 130 
#define  AREF_GROUND 129 
#define  AREF_OTHER 128 
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 

__attribute__((used)) static unsigned short rtd_convert_chan_gain(struct comedi_device *dev,
					    unsigned int chanspec, int index)
{
	const struct rtd_boardinfo *board = dev->board_ptr;
	unsigned int chan = CR_CHAN(chanspec);
	unsigned int range = CR_RANGE(chanspec);
	unsigned int aref = CR_AREF(chanspec);
	unsigned short r = 0;

	r |= chan & 0xf;

	/* Note: we also setup the channel list bipolar flag array */
	if (range < board->range_bip10) {
		/* +-5 range */
		r |= 0x000;
		r |= (range & 0x7) << 4;
	} else if (range < board->range_uni10) {
		/* +-10 range */
		r |= 0x100;
		r |= ((range - board->range_bip10) & 0x7) << 4;
	} else {
		/* +10 range */
		r |= 0x200;
		r |= ((range - board->range_uni10) & 0x7) << 4;
	}

	switch (aref) {
	case AREF_GROUND:	/* on-board ground */
		break;

	case AREF_COMMON:
		r |= 0x80;	/* ref external analog common */
		break;

	case AREF_DIFF:
		r |= 0x400;	/* differential inputs */
		break;

	case AREF_OTHER:	/* ??? */
		break;
	}
	return r;
}