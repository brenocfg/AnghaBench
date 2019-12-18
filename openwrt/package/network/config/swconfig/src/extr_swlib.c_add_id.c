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
struct nl_msg {int dummy; } ;
struct attrlist_arg {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT_U32 (struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_ATTR_ID ; 

__attribute__((used)) static int
add_id(struct nl_msg *msg, void *arg)
{
	struct attrlist_arg *l = arg;

	NLA_PUT_U32(msg, SWITCH_ATTR_ID, l->id);

	return 0;
nla_put_failure:
	return -1;
}