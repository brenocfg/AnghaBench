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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink_snapshot {int /*<<< orphan*/ * data; } ;
struct devlink_region {scalar_t__ size; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_REGION_SNAPSHOT_ID ; 
 scalar_t__ DEVLINK_REGION_READ_CHUNK_SIZE ; 
 int EINVAL ; 
 int devlink_nl_cmd_region_read_chunk_fill (struct sk_buff*,struct devlink*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct devlink_snapshot* devlink_region_snapshot_get_by_id (struct devlink_region*,scalar_t__) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int devlink_nl_region_read_snapshot_fill(struct sk_buff *skb,
						struct devlink *devlink,
						struct devlink_region *region,
						struct nlattr **attrs,
						u64 start_offset,
						u64 end_offset,
						bool dump,
						u64 *new_offset)
{
	struct devlink_snapshot *snapshot;
	u64 curr_offset = start_offset;
	u32 snapshot_id;
	int err = 0;

	*new_offset = start_offset;

	snapshot_id = nla_get_u32(attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID]);
	snapshot = devlink_region_snapshot_get_by_id(region, snapshot_id);
	if (!snapshot)
		return -EINVAL;

	if (end_offset > region->size || dump)
		end_offset = region->size;

	while (curr_offset < end_offset) {
		u32 data_size;
		u8 *data;

		if (end_offset - curr_offset < DEVLINK_REGION_READ_CHUNK_SIZE)
			data_size = end_offset - curr_offset;
		else
			data_size = DEVLINK_REGION_READ_CHUNK_SIZE;

		data = &snapshot->data[curr_offset];
		err = devlink_nl_cmd_region_read_chunk_fill(skb, devlink,
							    data, data_size,
							    curr_offset);
		if (err)
			break;

		curr_offset += data_size;
	}
	*new_offset = curr_offset;

	return err;
}