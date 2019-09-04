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
typedef  int u_char ;
typedef  int u32 ;
struct sym_hcb {int clock_khz; int clock_divn; int features; } ;

/* Variables and functions */
 int FE_C10 ; 
 int FE_U3EN ; 
 int* div_10M ; 

__attribute__((used)) static int 
sym_getsync(struct sym_hcb *np, u_char dt, u_char sfac, u_char *divp, u_char *fakp)
{
	u32	clk = np->clock_khz;	/* SCSI clock frequency in kHz	*/
	int	div = np->clock_divn;	/* Number of divisors supported	*/
	u32	fak;			/* Sync factor in sxfer		*/
	u32	per;			/* Period in tenths of ns	*/
	u32	kpc;			/* (per * clk)			*/
	int	ret;

	/*
	 *  Compute the synchronous period in tenths of nano-seconds
	 */
	if (dt && sfac <= 9)	per = 125;
	else if	(sfac <= 10)	per = 250;
	else if	(sfac == 11)	per = 303;
	else if	(sfac == 12)	per = 500;
	else			per = 40 * sfac;
	ret = per;

	kpc = per * clk;
	if (dt)
		kpc <<= 1;

	/*
	 *  For earliest C10 revision 0, we cannot use extra 
	 *  clocks for the setting of the SCSI clocking.
	 *  Note that this limits the lowest sync data transfer 
	 *  to 5 Mega-transfers per second and may result in
	 *  using higher clock divisors.
	 */
#if 1
	if ((np->features & (FE_C10|FE_U3EN)) == FE_C10) {
		/*
		 *  Look for the lowest clock divisor that allows an 
		 *  output speed not faster than the period.
		 */
		while (div > 0) {
			--div;
			if (kpc > (div_10M[div] << 2)) {
				++div;
				break;
			}
		}
		fak = 0;			/* No extra clocks */
		if (div == np->clock_divn) {	/* Are we too fast ? */
			ret = -1;
		}
		*divp = div;
		*fakp = fak;
		return ret;
	}
#endif

	/*
	 *  Look for the greatest clock divisor that allows an 
	 *  input speed faster than the period.
	 */
	while (--div > 0)
		if (kpc >= (div_10M[div] << 2)) break;

	/*
	 *  Calculate the lowest clock factor that allows an output 
	 *  speed not faster than the period, and the max output speed.
	 *  If fak >= 1 we will set both XCLKH_ST and XCLKH_DT.
	 *  If fak >= 2 we will also set XCLKS_ST and XCLKS_DT.
	 */
	if (dt) {
		fak = (kpc - 1) / (div_10M[div] << 1) + 1 - 2;
		/* ret = ((2+fak)*div_10M[div])/np->clock_khz; */
	} else {
		fak = (kpc - 1) / div_10M[div] + 1 - 4;
		/* ret = ((4+fak)*div_10M[div])/np->clock_khz; */
	}

	/*
	 *  Check against our hardware limits, or bugs :).
	 */
	if (fak > 2) {
		fak = 2;
		ret = -1;
	}

	/*
	 *  Compute and return sync parameters.
	 */
	*divp = div;
	*fakp = fak;

	return ret;
}