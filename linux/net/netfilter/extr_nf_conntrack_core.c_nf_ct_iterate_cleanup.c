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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 struct nf_conn* get_next_corpse (int (*) (struct nf_conn*,void*),void*,unsigned int*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  nf_conntrack_generation ; 
 int /*<<< orphan*/  nf_ct_delete (struct nf_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 unsigned int read_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void nf_ct_iterate_cleanup(int (*iter)(struct nf_conn *i, void *data),
				  void *data, u32 portid, int report)
{
	unsigned int bucket = 0, sequence;
	struct nf_conn *ct;

	might_sleep();

	for (;;) {
		sequence = read_seqcount_begin(&nf_conntrack_generation);

		while ((ct = get_next_corpse(iter, data, &bucket)) != NULL) {
			/* Time to push up daises... */

			nf_ct_delete(ct, portid, report);
			nf_ct_put(ct);
			cond_resched();
		}

		if (!read_seqcount_retry(&nf_conntrack_generation, sequence))
			break;
		bucket = 0;
	}
}