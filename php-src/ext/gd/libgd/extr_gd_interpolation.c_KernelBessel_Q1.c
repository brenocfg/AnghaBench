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

/* Variables and functions */

__attribute__((used)) static double KernelBessel_Q1(const double x)
{
	double p, q;

	register long i;

	static const double
	Pone[] =
	{
		0.3511751914303552822533318e+3,
		0.7210391804904475039280863e+3,
		0.4259873011654442389886993e+3,
		0.831898957673850827325226e+2,
		0.45681716295512267064405e+1,
		0.3532840052740123642735e-1
	},
	Qone[] =
	{
		0.74917374171809127714519505e+4,
		0.154141773392650970499848051e+5,
		0.91522317015169922705904727e+4,
		0.18111867005523513506724158e+4,
		0.1038187585462133728776636e+3,
		0.1e+1
	};

	p = Pone[5];
	q = Qone[5];
	for (i=4; i >= 0; i--)
	{
		p = p*(8.0/x)*(8.0/x)+Pone[i];
		q = q*(8.0/x)*(8.0/x)+Qone[i];
	}
	return (double)(p/q);
}