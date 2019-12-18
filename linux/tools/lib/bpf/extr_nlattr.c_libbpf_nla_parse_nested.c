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
struct libbpf_nla_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  libbpf_nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  libbpf_nla_len (struct nlattr*) ; 
 int libbpf_nla_parse (struct nlattr**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct libbpf_nla_policy*) ; 

int libbpf_nla_parse_nested(struct nlattr *tb[], int maxtype,
			    struct nlattr *nla,
			    struct libbpf_nla_policy *policy)
{
	return libbpf_nla_parse(tb, maxtype, libbpf_nla_data(nla),
				libbpf_nla_len(nla), policy);
}