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
struct tc_cookie {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t TCA_ACT_COOKIE ; 
 int /*<<< orphan*/  kfree (struct tc_cookie*) ; 
 struct tc_cookie* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memdup (struct nlattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tc_cookie *nla_memdup_cookie(struct nlattr **tb)
{
	struct tc_cookie *c = kzalloc(sizeof(*c), GFP_KERNEL);
	if (!c)
		return NULL;

	c->data = nla_memdup(tb[TCA_ACT_COOKIE], GFP_KERNEL);
	if (!c->data) {
		kfree(c);
		return NULL;
	}
	c->len = nla_len(tb[TCA_ACT_COOKIE]);

	return c;
}