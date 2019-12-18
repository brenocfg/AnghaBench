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
typedef  int /*<<< orphan*/  inet ;
typedef  int /*<<< orphan*/  SortSupport ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetInetPP (int /*<<< orphan*/ ) ; 
 int network_cmp_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
network_fast_cmp(Datum x, Datum y, SortSupport ssup)
{
	inet	   *arg1 = DatumGetInetPP(x);
	inet	   *arg2 = DatumGetInetPP(y);

	return network_cmp_internal(arg1, arg2);
}