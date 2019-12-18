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

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

int nft_parse_u32_check(const struct nlattr *attr, int max, u32 *dest)
{
	u32 val;

	val = ntohl(nla_get_be32(attr));
	if (val > max)
		return -ERANGE;

	*dest = val;
	return 0;
}