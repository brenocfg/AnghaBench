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
typedef  int u32 ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conncount_tuple {unsigned long jiffies32; int cpu; int /*<<< orphan*/  tuple; int /*<<< orphan*/  zone; } ;
struct nf_conncount_list {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOENT ; 
 struct nf_conntrack_tuple_hash const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_free (struct nf_conncount_list*,struct nf_conncount_tuple*) ; 
 scalar_t__ jiffies ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static const struct nf_conntrack_tuple_hash *
find_or_evict(struct net *net, struct nf_conncount_list *list,
	      struct nf_conncount_tuple *conn)
{
	const struct nf_conntrack_tuple_hash *found;
	unsigned long a, b;
	int cpu = raw_smp_processor_id();
	u32 age;

	found = nf_conntrack_find_get(net, &conn->zone, &conn->tuple);
	if (found)
		return found;
	b = conn->jiffies32;
	a = (u32)jiffies;

	/* conn might have been added just before by another cpu and
	 * might still be unconfirmed.  In this case, nf_conntrack_find()
	 * returns no result.  Thus only evict if this cpu added the
	 * stale entry or if the entry is older than two jiffies.
	 */
	age = a - b;
	if (conn->cpu == cpu || age >= 2) {
		conn_free(list, conn);
		return ERR_PTR(-ENOENT);
	}

	return ERR_PTR(-EAGAIN);
}