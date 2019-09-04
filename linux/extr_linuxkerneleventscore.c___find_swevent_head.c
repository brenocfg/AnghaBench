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
typedef  size_t u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct swevent_hlist {struct hlist_head* heads; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 size_t swevent_hash (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hlist_head *
__find_swevent_head(struct swevent_hlist *hlist, u64 type, u32 event_id)
{
	u64 hash = swevent_hash(type, event_id);

	return &hlist->heads[hash];
}