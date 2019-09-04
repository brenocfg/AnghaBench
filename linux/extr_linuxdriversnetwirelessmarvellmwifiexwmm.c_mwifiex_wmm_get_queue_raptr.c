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
struct mwifiex_ra_list_tbl {int dummy; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_ralist_add (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 
 struct mwifiex_ra_list_tbl* mwifiex_wmm_get_ralist_node (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

struct mwifiex_ra_list_tbl *
mwifiex_wmm_get_queue_raptr(struct mwifiex_private *priv, u8 tid,
			    const u8 *ra_addr)
{
	struct mwifiex_ra_list_tbl *ra_list;

	ra_list = mwifiex_wmm_get_ralist_node(priv, tid, ra_addr);
	if (ra_list)
		return ra_list;
	mwifiex_ralist_add(priv, ra_addr);

	return mwifiex_wmm_get_ralist_node(priv, tid, ra_addr);
}