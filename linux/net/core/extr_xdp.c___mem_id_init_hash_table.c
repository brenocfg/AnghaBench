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
struct rhashtable {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct rhashtable*) ; 
 struct rhashtable* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct rhashtable* mem_id_ht ; 
 int mem_id_init ; 
 int /*<<< orphan*/  mem_id_rht_params ; 
 int rhashtable_init (struct rhashtable*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __mem_id_init_hash_table(void)
{
	struct rhashtable *rht;
	int ret;

	if (unlikely(mem_id_init))
		return 0;

	rht = kzalloc(sizeof(*rht), GFP_KERNEL);
	if (!rht)
		return -ENOMEM;

	ret = rhashtable_init(rht, &mem_id_rht_params);
	if (ret < 0) {
		kfree(rht);
		return ret;
	}
	mem_id_ht = rht;
	smp_mb(); /* mutex lock should provide enough pairing */
	mem_id_init = true;

	return 0;
}