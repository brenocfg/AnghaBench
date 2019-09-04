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
struct matrox_pll_limits {unsigned int vcomax; unsigned int vcomin; } ;
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 unsigned int g450_f2vco (unsigned int,unsigned int) ; 
 unsigned int g450_nextpll (struct matrox_fb_info const*,struct matrox_pll_limits const*,unsigned int*,int) ; 

__attribute__((used)) static unsigned int g450_firstpll(const struct matrox_fb_info *minfo,
				  const struct matrox_pll_limits *pi,
				  unsigned int *vco, unsigned int fout)
{
	unsigned int p;
	unsigned int vcomax;

	vcomax = pi->vcomax;
	if (fout > (vcomax / 2)) {
		if (fout > vcomax) {
			*vco = vcomax;
		} else {
			*vco = fout;
		}
		p = 0x40;
	} else {
		unsigned int tvco;

		p = 3;
		tvco = g450_f2vco(p, fout);
		while (p && (tvco > vcomax)) {
			p--;
			tvco >>= 1;
		}
		if (tvco < pi->vcomin) {
			tvco = pi->vcomin;
		}
		*vco = tvco;
	}
	return g450_nextpll(minfo, pi, vco, 0xFF0000 | p);
}