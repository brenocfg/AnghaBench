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
struct hmap_elem {int cnt; int /*<<< orphan*/  lock; } ;
struct cls_elem {int /*<<< orphan*/  lock; int /*<<< orphan*/  cnt; } ;
struct bpf_vqueue {int volatile credit; unsigned long long lasttime; int /*<<< orphan*/  lock; int /*<<< orphan*/  rate; } ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ CREDIT_PER_NS (unsigned long long,int /*<<< orphan*/ ) ; 
 struct cls_elem* bpf_get_local_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long long bpf_ktime_get_ns () ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int*,struct hmap_elem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cls_map ; 
 int /*<<< orphan*/  hmap ; 
 int /*<<< orphan*/  vqueue ; 

int bpf_sping_lock_test(struct __sk_buff *skb)
{
	volatile int credit = 0, max_credit = 100, pkt_len = 64;
	struct hmap_elem zero = {}, *val;
	unsigned long long curtime;
	struct bpf_vqueue *q;
	struct cls_elem *cls;
	int key = 0;
	int err = 0;

	val = bpf_map_lookup_elem(&hmap, &key);
	if (!val) {
		bpf_map_update_elem(&hmap, &key, &zero, 0);
		val = bpf_map_lookup_elem(&hmap, &key);
		if (!val) {
			err = 1;
			goto err;
		}
	}
	/* spin_lock in hash map run time test */
	bpf_spin_lock(&val->lock);
	if (val->cnt)
		val->cnt--;
	else
		val->cnt++;
	if (val->cnt != 0 && val->cnt != 1)
		err = 1;
	bpf_spin_unlock(&val->lock);

	/* spin_lock in array. virtual queue demo */
	q = bpf_map_lookup_elem(&vqueue, &key);
	if (!q)
		goto err;
	curtime = bpf_ktime_get_ns();
	bpf_spin_lock(&q->lock);
	q->credit += CREDIT_PER_NS(curtime - q->lasttime, q->rate);
	q->lasttime = curtime;
	if (q->credit > max_credit)
		q->credit = max_credit;
	q->credit -= pkt_len;
	credit = q->credit;
	bpf_spin_unlock(&q->lock);

	/* spin_lock in cgroup local storage */
	cls = bpf_get_local_storage(&cls_map, 0);
	bpf_spin_lock(&cls->lock);
	cls->cnt++;
	bpf_spin_unlock(&cls->lock);

err:
	return err;
}