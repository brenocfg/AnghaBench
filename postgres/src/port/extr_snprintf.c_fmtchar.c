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
typedef  int /*<<< orphan*/  PrintfTarget ;

/* Variables and functions */
 int compute_padlen (int,int,int) ; 
 int /*<<< orphan*/  dopr_outch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dopr_outchmulti (char,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trailing_pad (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fmtchar(int value, int leftjust, int minlen, PrintfTarget *target)
{
	int			padlen;			/* amount to pad */

	padlen = compute_padlen(minlen, 1, leftjust);

	if (padlen > 0)
	{
		dopr_outchmulti(' ', padlen, target);
		padlen = 0;
	}

	dopr_outch(value, target);

	trailing_pad(padlen, target);
}