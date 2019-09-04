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
struct fbtft_par {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int GAMMA_LEN ; 
 int GAMMA_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int set_gamma(struct fbtft_par *par, u32 *curves)
{
	unsigned long tmp[GAMMA_NUM * GAMMA_LEN];
	int i, acc = 0;

	for (i = 0; i < 63; i++) {
		if (i > 0 && curves[i] < 2) {
			dev_err(par->info->device,
				"Illegal value in Grayscale Lookup Table at index %d : %d. Must be greater than 1\n",
				i, curves[i]);
			return -EINVAL;
		}
		acc += curves[i];
		tmp[i] = acc;
		if (acc > 180) {
			dev_err(par->info->device,
				"Illegal value(s) in Grayscale Lookup Table. At index=%d : %d, the accumulated value has exceeded 180\n",
				i, acc);
			return -EINVAL;
		}
	}

	write_reg(par, 0xB8,
		  tmp[0],  tmp[1],  tmp[2],  tmp[3],
		  tmp[4],  tmp[5],  tmp[6],  tmp[7],
		  tmp[8],  tmp[9],  tmp[10], tmp[11],
		  tmp[12], tmp[13], tmp[14], tmp[15],
		  tmp[16], tmp[17], tmp[18], tmp[19],
		  tmp[20], tmp[21], tmp[22], tmp[23],
		  tmp[24], tmp[25], tmp[26], tmp[27],
		  tmp[28], tmp[29], tmp[30], tmp[31],
		  tmp[32], tmp[33], tmp[34], tmp[35],
		  tmp[36], tmp[37], tmp[38], tmp[39],
		  tmp[40], tmp[41], tmp[42], tmp[43],
		  tmp[44], tmp[45], tmp[46], tmp[47],
		  tmp[48], tmp[49], tmp[50], tmp[51],
		  tmp[52], tmp[53], tmp[54], tmp[55],
		  tmp[56], tmp[57], tmp[58], tmp[59],
		  tmp[60], tmp[61], tmp[62]);

	return 0;
}