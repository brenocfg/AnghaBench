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
struct z3fold_pool {int /*<<< orphan*/  unbuddied; int /*<<< orphan*/  lock; } ;
struct z3fold_header {scalar_t__ first_chunks; scalar_t__ last_chunks; scalar_t__ middle_chunks; int /*<<< orphan*/  cpu; int /*<<< orphan*/  buddy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 struct list_head* get_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int num_free_chunks (struct z3fold_header*) ; 
 int /*<<< orphan*/  put_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void add_to_unbuddied(struct z3fold_pool *pool,
				struct z3fold_header *zhdr)
{
	if (zhdr->first_chunks == 0 || zhdr->last_chunks == 0 ||
			zhdr->middle_chunks == 0) {
		struct list_head *unbuddied = get_cpu_ptr(pool->unbuddied);

		int freechunks = num_free_chunks(zhdr);
		spin_lock(&pool->lock);
		list_add(&zhdr->buddy, &unbuddied[freechunks]);
		spin_unlock(&pool->lock);
		zhdr->cpu = smp_processor_id();
		put_cpu_ptr(pool->unbuddied);
	}
}