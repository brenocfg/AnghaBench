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
struct ip_vs_service {struct ip_vs_lblcr_table* sched_data; } ;
struct ip_vs_lblcr_table {int max_size; int counter; int dead; int /*<<< orphan*/  periodic_timer; int /*<<< orphan*/  entries; struct ip_vs_service* svc; scalar_t__ rover; int /*<<< orphan*/ * bucket; } ;

/* Variables and functions */
 scalar_t__ CHECK_EXPIRE_INTERVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int) ; 
 int IP_VS_LBLCR_TAB_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_lblcr_check_expire ; 
 scalar_t__ jiffies ; 
 struct ip_vs_lblcr_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_lblcr_init_svc(struct ip_vs_service *svc)
{
	int i;
	struct ip_vs_lblcr_table *tbl;

	/*
	 *    Allocate the ip_vs_lblcr_table for this service
	 */
	tbl = kmalloc(sizeof(*tbl), GFP_KERNEL);
	if (tbl == NULL)
		return -ENOMEM;

	svc->sched_data = tbl;
	IP_VS_DBG(6, "LBLCR hash table (memory=%zdbytes) allocated for "
		  "current service\n", sizeof(*tbl));

	/*
	 *    Initialize the hash buckets
	 */
	for (i = 0; i < IP_VS_LBLCR_TAB_SIZE; i++) {
		INIT_HLIST_HEAD(&tbl->bucket[i]);
	}
	tbl->max_size = IP_VS_LBLCR_TAB_SIZE*16;
	tbl->rover = 0;
	tbl->counter = 1;
	tbl->dead = false;
	tbl->svc = svc;
	atomic_set(&tbl->entries, 0);

	/*
	 *    Hook periodic timer for garbage collection
	 */
	timer_setup(&tbl->periodic_timer, ip_vs_lblcr_check_expire, 0);
	mod_timer(&tbl->periodic_timer, jiffies + CHECK_EXPIRE_INTERVAL);

	return 0;
}