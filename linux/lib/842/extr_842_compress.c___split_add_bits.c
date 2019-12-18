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
typedef  int u8 ;
typedef  int u64 ;
struct sw842_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 int add_bits (struct sw842_param*,int,int) ; 

__attribute__((used)) static int __split_add_bits(struct sw842_param *p, u64 d, u8 n, u8 s)
{
	int ret;

	if (n <= s)
		return -EINVAL;

	ret = add_bits(p, d >> s, n - s);
	if (ret)
		return ret;
	return add_bits(p, d & GENMASK_ULL(s - 1, 0), s);
}