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
struct hmap_elem {int* var; int /*<<< orphan*/  lock; } ;
struct array_elem {int* var; int /*<<< orphan*/  lock; } ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int VAR_NUM ; 
 int /*<<< orphan*/  array_map ; 
 int bpf_get_prandom_u32 () ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  bpf_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_map ; 

int bpf_map_lock_test(struct __sk_buff *skb)
{
	struct hmap_elem zero = {}, *val;
	int rnd = bpf_get_prandom_u32();
	int key = 0, err = 1, i;
	struct array_elem *q;

	val = bpf_map_lookup_elem(&hash_map, &key);
	if (!val)
		goto err;
	/* spin_lock in hash map */
	bpf_spin_lock(&val->lock);
	for (i = 0; i < VAR_NUM; i++)
		val->var[i] = rnd;
	bpf_spin_unlock(&val->lock);

	/* spin_lock in array */
	q = bpf_map_lookup_elem(&array_map, &key);
	if (!q)
		goto err;
	bpf_spin_lock(&q->lock);
	for (i = 0; i < VAR_NUM; i++)
		q->var[i] = rnd;
	bpf_spin_unlock(&q->lock);
	err = 0;
err:
	return err;
}