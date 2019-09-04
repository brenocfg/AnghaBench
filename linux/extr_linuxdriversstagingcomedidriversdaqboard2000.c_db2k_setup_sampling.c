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
typedef  int u16 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  db2k_write_acq_scan_list_entry (struct comedi_device*,int) ; 

__attribute__((used)) static void db2k_setup_sampling(struct comedi_device *dev, int chan, int gain)
{
	u16 word0, word1, word2, word3;

	/* Channel 0-7 diff, channel 8-23 single ended */
	word0 = 0;
	word1 = 0x0004;		/* Last scan */
	word2 = (chan << 6) & 0x00c0;
	switch (chan / 4) {
	case 0:
		word3 = 0x0001;
		break;
	case 1:
		word3 = 0x0002;
		break;
	case 2:
		word3 = 0x0005;
		break;
	case 3:
		word3 = 0x0006;
		break;
	case 4:
		word3 = 0x0041;
		break;
	case 5:
		word3 = 0x0042;
		break;
	default:
		word3 = 0;
		break;
	}
	/* These should be read from EEPROM */
	word2 |= 0x0800;	/* offset */
	word3 |= 0xc000;	/* gain */
	db2k_write_acq_scan_list_entry(dev, word0);
	db2k_write_acq_scan_list_entry(dev, word1);
	db2k_write_acq_scan_list_entry(dev, word2);
	db2k_write_acq_scan_list_entry(dev, word3);
}