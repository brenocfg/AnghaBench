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
struct sw_flow_actions {int dummy; } ;
struct nlattr {int nla_type; int nla_len; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nlattr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_attr_size (int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_padlen (int) ; 
 struct nlattr* reserve_sfa_size (struct sw_flow_actions**,int,int) ; 

__attribute__((used)) static struct nlattr *__add_action(struct sw_flow_actions **sfa,
				   int attrtype, void *data, int len, bool log)
{
	struct nlattr *a;

	a = reserve_sfa_size(sfa, nla_attr_size(len), log);
	if (IS_ERR(a))
		return a;

	a->nla_type = attrtype;
	a->nla_len = nla_attr_size(len);

	if (data)
		memcpy(nla_data(a), data, len);
	memset((unsigned char *) a + a->nla_len, 0, nla_padlen(len));

	return a;
}