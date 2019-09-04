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
struct nlattr {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int
nfnetlink_parse_nat_setup(struct nf_conn *ct,
			  enum nf_nat_manip_type manip,
			  const struct nlattr *attr)
{
	return -EOPNOTSUPP;
}