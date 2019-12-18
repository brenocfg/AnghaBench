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
struct napi_struct {scalar_t__ gro_bitmask; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_gro_hash (struct napi_struct*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  napi_free_frags (struct napi_struct*) ; 
 scalar_t__ napi_hash_del (struct napi_struct*) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void netif_napi_del(struct napi_struct *napi)
{
	might_sleep();
	if (napi_hash_del(napi))
		synchronize_net();
	list_del_init(&napi->dev_list);
	napi_free_frags(napi);

	flush_gro_hash(napi);
	napi->gro_bitmask = 0;
}