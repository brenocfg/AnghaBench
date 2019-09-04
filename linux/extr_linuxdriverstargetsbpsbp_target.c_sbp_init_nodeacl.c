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
typedef  int /*<<< orphan*/  u64 ;
struct se_node_acl {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ sbp_parse_wwn (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sbp_init_nodeacl(struct se_node_acl *se_nacl, const char *name)
{
	u64 guid = 0;

	if (sbp_parse_wwn(name, &guid) < 0)
		return -EINVAL;
	return 0;
}