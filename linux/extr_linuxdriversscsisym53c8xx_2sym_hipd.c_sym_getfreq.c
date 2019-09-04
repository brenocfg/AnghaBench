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
typedef  scalar_t__ u_int ;
struct sym_hcb {int dummy; } ;

/* Variables and functions */
 scalar_t__ getfreq (struct sym_hcb*,int) ; 

__attribute__((used)) static unsigned sym_getfreq (struct sym_hcb *np)
{
	u_int f1, f2;
	int gen = 8;

	getfreq (np, gen);	/* throw away first result */
	f1 = getfreq (np, gen);
	f2 = getfreq (np, gen);
	if (f1 > f2) f1 = f2;		/* trust lower result	*/
	return f1;
}