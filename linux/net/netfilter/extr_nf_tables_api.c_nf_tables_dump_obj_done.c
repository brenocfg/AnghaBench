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
struct nft_obj_filter {struct nft_obj_filter* table; } ;
struct netlink_callback {struct nft_obj_filter* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nft_obj_filter*) ; 

__attribute__((used)) static int nf_tables_dump_obj_done(struct netlink_callback *cb)
{
	struct nft_obj_filter *filter = cb->data;

	if (filter) {
		kfree(filter->table);
		kfree(filter);
	}

	return 0;
}