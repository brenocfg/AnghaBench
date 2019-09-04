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
typedef  size_t uint8_t ;
struct xt_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct xt_match* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct xt_match*) ; 
 scalar_t__ XT_EXTENSION_MAXNAMELEN ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strnlen (char const*,scalar_t__) ; 
 struct xt_match* xt_find_match (size_t,char const*,size_t) ; 
 int /*<<< orphan*/ * xt_prefix ; 

struct xt_match *
xt_request_find_match(uint8_t nfproto, const char *name, uint8_t revision)
{
	struct xt_match *match;

	if (strnlen(name, XT_EXTENSION_MAXNAMELEN) == XT_EXTENSION_MAXNAMELEN)
		return ERR_PTR(-EINVAL);

	match = xt_find_match(nfproto, name, revision);
	if (IS_ERR(match)) {
		request_module("%st_%s", xt_prefix[nfproto], name);
		match = xt_find_match(nfproto, name, revision);
	}

	return match;
}