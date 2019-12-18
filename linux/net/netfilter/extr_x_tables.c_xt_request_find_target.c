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
typedef  size_t u8 ;
struct xt_target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct xt_target* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct xt_target*) ; 
 scalar_t__ XT_EXTENSION_MAXNAMELEN ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strnlen (char const*,scalar_t__) ; 
 struct xt_target* xt_find_target (size_t,char const*,size_t) ; 
 int /*<<< orphan*/ * xt_prefix ; 

struct xt_target *xt_request_find_target(u8 af, const char *name, u8 revision)
{
	struct xt_target *target;

	if (strnlen(name, XT_EXTENSION_MAXNAMELEN) == XT_EXTENSION_MAXNAMELEN)
		return ERR_PTR(-EINVAL);

	target = xt_find_target(af, name, revision);
	if (IS_ERR(target)) {
		request_module("%st_%s", xt_prefix[af], name);
		target = xt_find_target(af, name, revision);
	}

	return target;
}