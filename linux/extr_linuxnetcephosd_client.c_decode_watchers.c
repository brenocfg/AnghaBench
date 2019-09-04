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
typedef  int u32 ;
struct ceph_watch_item {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int ceph_decode_32 (void**) ; 
 int ceph_start_decoding (void**,void*,int,char*,int /*<<< orphan*/ *,int*) ; 
 int decode_watcher (void**,void*,struct ceph_watch_item*) ; 
 struct ceph_watch_item* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ceph_watch_item*) ; 

__attribute__((used)) static int decode_watchers(void **p, void *end,
			   struct ceph_watch_item **watchers,
			   u32 *num_watchers)
{
	u8 struct_v;
	u32 struct_len;
	int i;
	int ret;

	ret = ceph_start_decoding(p, end, 1, "obj_list_watch_response_t",
				  &struct_v, &struct_len);
	if (ret)
		return ret;

	*num_watchers = ceph_decode_32(p);
	*watchers = kcalloc(*num_watchers, sizeof(**watchers), GFP_NOIO);
	if (!*watchers)
		return -ENOMEM;

	for (i = 0; i < *num_watchers; i++) {
		ret = decode_watcher(p, end, *watchers + i);
		if (ret) {
			kfree(*watchers);
			return ret;
		}
	}

	return 0;
}