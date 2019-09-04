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
struct tga_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFFCHECK (int) ; 
 int /*<<< orphan*/  TGA_CLOCK_REG ; 
 int TGA_PLL_BASE_FREQ ; 
 int TGA_PLL_MAX_FREQ ; 
 int /*<<< orphan*/  TGA_WRITE_REG (struct tga_par*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tgafb_set_pll(struct tga_par *par, int f)
{
	int n, shift, base, min_diff, target;
	int r,a,m,vm = 34, va = 1, vr = 30;

	for (r = 0 ; r < 12 ; r++)
		TGA_WRITE_REG(par, !r, TGA_CLOCK_REG);

	if (f > TGA_PLL_MAX_FREQ)
		f = TGA_PLL_MAX_FREQ;

	if (f >= TGA_PLL_MAX_FREQ / 2)
		shift = 0;
	else if (f >= TGA_PLL_MAX_FREQ / 4)
		shift = 1;
	else
		shift = 2;

	TGA_WRITE_REG(par, shift & 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, shift >> 1, TGA_CLOCK_REG);

	for (r = 0 ; r < 10 ; r++)
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);

	if (f <= 120000) {
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	}
	else if (f <= 200000) {
		TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	}
	else {
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
		TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
	}

	TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);

	target = (f << shift) / TGA_PLL_BASE_FREQ;
	min_diff = TGA_PLL_MAX_FREQ;

	r = 7 / target;
	if (!r) r = 1;

	base = target * r;
	while (base < 449) {
		for (n = base < 7 ? 7 : base; n < base + target && n < 449; n++) {
			m = ((n + 3) / 7) - 1;
			a = 0;
			DIFFCHECK((m + 1) * 7);
			m++;
			DIFFCHECK((m + 1) * 7);
			m = (n / 6) - 1;
			if ((a = n % 6))
				DIFFCHECK(n);
		}
		r++;
		base += target;
	}

	vr--;

	for (r = 0; r < 8; r++)
		TGA_WRITE_REG(par, (vm >> r) & 1, TGA_CLOCK_REG);
	for (r = 0; r < 8 ; r++)
		TGA_WRITE_REG(par, (va >> r) & 1, TGA_CLOCK_REG);
	for (r = 0; r < 7 ; r++)
		TGA_WRITE_REG(par, (vr >> r) & 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, ((vr >> 7) & 1)|2, TGA_CLOCK_REG);
}