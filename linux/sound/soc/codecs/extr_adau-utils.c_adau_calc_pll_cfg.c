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
typedef  int uint8_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int EINVAL ; 
 unsigned int gcd (unsigned int,unsigned int) ; 

int adau_calc_pll_cfg(unsigned int freq_in, unsigned int freq_out,
	uint8_t regs[5])
{
	unsigned int r, n, m, i, j;
	unsigned int div;

	if (!freq_out) {
		r = 0;
		n = 0;
		m = 0;
		div = 0;
	} else {
		if (freq_out % freq_in != 0) {
			div = DIV_ROUND_UP(freq_in, 13500000);
			freq_in /= div;
			r = freq_out / freq_in;
			i = freq_out % freq_in;
			j = gcd(i, freq_in);
			n = i / j;
			m = freq_in / j;
			div--;
		} else {
			r = freq_out / freq_in;
			n = 0;
			m = 0;
			div = 0;
		}
		if (n > 0xffff || m > 0xffff || div > 3 || r > 8 || r < 2)
			return -EINVAL;
	}

	regs[0] = m >> 8;
	regs[1] = m & 0xff;
	regs[2] = n >> 8;
	regs[3] = n & 0xff;
	regs[4] = (r << 3) | (div << 1);
	if (m != 0)
		regs[4] |= 1; /* Fractional mode */

	return 0;
}