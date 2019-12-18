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
struct key_params {scalar_t__ cipher; scalar_t__ seq; int /*<<< orphan*/  seq_len; scalar_t__ key; int /*<<< orphan*/  key_len; } ;
struct get_key_cookie {int error; int /*<<< orphan*/  msg; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_KEY ; 
 int /*<<< orphan*/  NL80211_ATTR_KEY_CIPHER ; 
 int /*<<< orphan*/  NL80211_ATTR_KEY_DATA ; 
 int /*<<< orphan*/  NL80211_ATTR_KEY_SEQ ; 
 int /*<<< orphan*/  NL80211_KEY_CIPHER ; 
 int /*<<< orphan*/  NL80211_KEY_DATA ; 
 int /*<<< orphan*/  NL80211_KEY_IDX ; 
 int /*<<< orphan*/  NL80211_KEY_SEQ ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_key_callback(void *c, struct key_params *params)
{
	struct nlattr *key;
	struct get_key_cookie *cookie = c;

	if ((params->key &&
	     nla_put(cookie->msg, NL80211_ATTR_KEY_DATA,
		     params->key_len, params->key)) ||
	    (params->seq &&
	     nla_put(cookie->msg, NL80211_ATTR_KEY_SEQ,
		     params->seq_len, params->seq)) ||
	    (params->cipher &&
	     nla_put_u32(cookie->msg, NL80211_ATTR_KEY_CIPHER,
			 params->cipher)))
		goto nla_put_failure;

	key = nla_nest_start_noflag(cookie->msg, NL80211_ATTR_KEY);
	if (!key)
		goto nla_put_failure;

	if ((params->key &&
	     nla_put(cookie->msg, NL80211_KEY_DATA,
		     params->key_len, params->key)) ||
	    (params->seq &&
	     nla_put(cookie->msg, NL80211_KEY_SEQ,
		     params->seq_len, params->seq)) ||
	    (params->cipher &&
	     nla_put_u32(cookie->msg, NL80211_KEY_CIPHER,
			 params->cipher)))
		goto nla_put_failure;

	if (nla_put_u8(cookie->msg, NL80211_KEY_IDX, cookie->idx))
		goto nla_put_failure;

	nla_nest_end(cookie->msg, key);

	return;
 nla_put_failure:
	cookie->error = 1;
}