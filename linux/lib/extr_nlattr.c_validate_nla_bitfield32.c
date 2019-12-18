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
typedef  int u32 ;
struct nlattr {int dummy; } ;
struct nla_bitfield32 {int const selector; int const value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nla_bitfield32* nla_data (struct nlattr const*) ; 

__attribute__((used)) static int validate_nla_bitfield32(const struct nlattr *nla,
				   const u32 *valid_flags_mask)
{
	const struct nla_bitfield32 *bf = nla_data(nla);

	if (!valid_flags_mask)
		return -EINVAL;

	/*disallow invalid bit selector */
	if (bf->selector & ~*valid_flags_mask)
		return -EINVAL;

	/*disallow invalid bit values */
	if (bf->value & ~*valid_flags_mask)
		return -EINVAL;

	/*disallow valid bit values that are not selected*/
	if (bf->value & ~bf->selector)
		return -EINVAL;

	return 0;
}