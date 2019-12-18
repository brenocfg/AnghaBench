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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PAD ; 
 int /*<<< orphan*/  DEVLINK_ATTR_REGION_CHUNK ; 
 int /*<<< orphan*/  DEVLINK_ATTR_REGION_CHUNK_ADDR ; 
 int /*<<< orphan*/  DEVLINK_ATTR_REGION_CHUNK_DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_region_read_chunk_fill(struct sk_buff *msg,
						 struct devlink *devlink,
						 u8 *chunk, u32 chunk_size,
						 u64 addr)
{
	struct nlattr *chunk_attr;
	int err;

	chunk_attr = nla_nest_start_noflag(msg, DEVLINK_ATTR_REGION_CHUNK);
	if (!chunk_attr)
		return -EINVAL;

	err = nla_put(msg, DEVLINK_ATTR_REGION_CHUNK_DATA, chunk_size, chunk);
	if (err)
		goto nla_put_failure;

	err = nla_put_u64_64bit(msg, DEVLINK_ATTR_REGION_CHUNK_ADDR, addr,
				DEVLINK_ATTR_PAD);
	if (err)
		goto nla_put_failure;

	nla_nest_end(msg, chunk_attr);
	return 0;

nla_put_failure:
	nla_nest_cancel(msg, chunk_attr);
	return err;
}