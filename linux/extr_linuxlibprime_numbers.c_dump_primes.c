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
struct primes {int /*<<< orphan*/  sz; int /*<<< orphan*/ * primes; int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_print_to_pagebuf (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  primes ; 
 struct primes* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void dump_primes(void)
{
	const struct primes *p;
	char *buf;

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);

	rcu_read_lock();
	p = rcu_dereference(primes);

	if (buf)
		bitmap_print_to_pagebuf(true, buf, p->primes, p->sz);
	pr_info("primes.{last=%lu, .sz=%lu, .primes[]=...x%lx} = %s",
		p->last, p->sz, p->primes[BITS_TO_LONGS(p->sz) - 1], buf);

	rcu_read_unlock();

	kfree(buf);
}