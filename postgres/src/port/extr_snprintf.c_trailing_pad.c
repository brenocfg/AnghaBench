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
 int /*<<< orphan*/  dopr_outchmulti (char,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
trailing_pad(int padlen, PrintfTarget *target)
{
	if (padlen < 0)
		dopr_outchmulti(' ', -padlen, target);
}