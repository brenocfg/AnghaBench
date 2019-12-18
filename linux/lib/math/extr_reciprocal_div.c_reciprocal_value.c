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
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct reciprocal_value {int m; int /*<<< orphan*/  sh2; int /*<<< orphan*/  sh1; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int fls (int) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

struct reciprocal_value reciprocal_value(u32 d)
{
	struct reciprocal_value R;
	u64 m;
	int l;

	l = fls(d - 1);
	m = ((1ULL << 32) * ((1ULL << l) - d));
	do_div(m, d);
	++m;
	R.m = (u32)m;
	R.sh1 = min(l, 1);
	R.sh2 = max(l - 1, 0);

	return R;
}