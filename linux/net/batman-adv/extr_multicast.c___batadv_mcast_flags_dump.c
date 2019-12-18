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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; } ;
struct netlink_callback {int dummy; } ;
struct batadv_priv {struct batadv_hashtable* orig_hash; } ;
struct batadv_hashtable {long size; } ;

/* Variables and functions */
 scalar_t__ batadv_mcast_flags_dump_bucket (struct sk_buff*,int /*<<< orphan*/ ,struct netlink_callback*,struct batadv_hashtable*,long,long*) ; 

__attribute__((used)) static int
__batadv_mcast_flags_dump(struct sk_buff *msg, u32 portid,
			  struct netlink_callback *cb,
			  struct batadv_priv *bat_priv, long *bucket, long *idx)
{
	struct batadv_hashtable *hash = bat_priv->orig_hash;
	long bucket_tmp = *bucket;
	long idx_tmp = *idx;

	while (bucket_tmp < hash->size) {
		if (batadv_mcast_flags_dump_bucket(msg, portid, cb, hash,
						   bucket_tmp, &idx_tmp))
			break;

		bucket_tmp++;
		idx_tmp = 0;
	}

	*bucket = bucket_tmp;
	*idx = idx_tmp;

	return msg->len;
}