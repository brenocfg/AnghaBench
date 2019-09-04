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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_ra_list_tbl {scalar_t__ total_pkt_count; int /*<<< orphan*/  ra; int /*<<< orphan*/  skb_head; int /*<<< orphan*/  list; } ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mwifiex_ra_list_tbl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,struct mwifiex_ra_list_tbl*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mwifiex_ra_list_tbl *
mwifiex_wmm_allocate_ralist_node(struct mwifiex_adapter *adapter, const u8 *ra)
{
	struct mwifiex_ra_list_tbl *ra_list;

	ra_list = kzalloc(sizeof(struct mwifiex_ra_list_tbl), GFP_ATOMIC);
	if (!ra_list)
		return NULL;

	INIT_LIST_HEAD(&ra_list->list);
	skb_queue_head_init(&ra_list->skb_head);

	memcpy(ra_list->ra, ra, ETH_ALEN);

	ra_list->total_pkt_count = 0;

	mwifiex_dbg(adapter, INFO, "info: allocated ra_list %p\n", ra_list);

	return ra_list;
}