#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct text_match {TYPE_2__* config; int /*<<< orphan*/  to_layer; int /*<<< orphan*/  from_layer; int /*<<< orphan*/  to_offset; int /*<<< orphan*/  from_offset; } ;
struct tcf_ematch {int dummy; } ;
struct tcf_em_text {int /*<<< orphan*/  pattern_len; scalar_t__ pad; int /*<<< orphan*/  to_layer; int /*<<< orphan*/  from_layer; int /*<<< orphan*/  to_offset; int /*<<< orphan*/  from_offset; int /*<<< orphan*/  algo; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  conf ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct text_match* EM_TEXT_PRIV (struct tcf_ematch*) ; 
 scalar_t__ nla_append (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_nohdr (struct sk_buff*,int,struct tcf_em_text*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  textsearch_get_pattern (TYPE_2__*) ; 
 int /*<<< orphan*/  textsearch_get_pattern_len (TYPE_2__*) ; 

__attribute__((used)) static int em_text_dump(struct sk_buff *skb, struct tcf_ematch *m)
{
	struct text_match *tm = EM_TEXT_PRIV(m);
	struct tcf_em_text conf;

	strncpy(conf.algo, tm->config->ops->name, sizeof(conf.algo) - 1);
	conf.from_offset = tm->from_offset;
	conf.to_offset = tm->to_offset;
	conf.from_layer = tm->from_layer;
	conf.to_layer = tm->to_layer;
	conf.pattern_len = textsearch_get_pattern_len(tm->config);
	conf.pad = 0;

	if (nla_put_nohdr(skb, sizeof(conf), &conf) < 0)
		goto nla_put_failure;
	if (nla_append(skb, conf.pattern_len,
		       textsearch_get_pattern(tm->config)) < 0)
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}