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
struct nla_policy {int dummy; } ;

/* Variables and functions */
 int NLA_ALIGN (int) ; 
 int /*<<< orphan*/  memset (struct nlattr**,int /*<<< orphan*/ ,int) ; 
 int nla_attr_size (int /*<<< orphan*/ ) ; 
 int nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_deprecated (struct nlattr**,int,int,int,struct nla_policy const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_attr(struct nlattr *tb[], int maxtype, struct nlattr *nla,
		      const struct nla_policy *policy, int len)
{
	int nested_len = nla_len(nla) - NLA_ALIGN(len);

	if (nested_len >= nla_attr_size(0))
		return nla_parse_deprecated(tb, maxtype,
					    nla_data(nla) + NLA_ALIGN(len),
					    nested_len, policy, NULL);

	memset(tb, 0, sizeof(struct nlattr *) * (maxtype + 1));
	return 0;
}