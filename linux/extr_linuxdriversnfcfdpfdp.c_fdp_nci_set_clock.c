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
typedef  char u8 ;
typedef  int u32 ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int fdp_nci_set_production_data (struct nci_dev*,int,char*) ; 

__attribute__((used)) static int fdp_nci_set_clock(struct nci_dev *ndev, u8 clock_type,
			     u32 clock_freq)
{
	u32 fc = 13560;
	u32 nd, num, delta;
	char data[9];

	nd = (24 * fc) / clock_freq;
	delta = 24 * fc - nd * clock_freq;
	num = (32768 * delta) / clock_freq;

	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;

	data[3] = 0x10;
	data[4] = 0x04;
	data[5] = num & 0xFF;
	data[6] = (num >> 8) & 0xff;
	data[7] = nd;
	data[8] = clock_type;

	return fdp_nci_set_production_data(ndev, 9, data);
}