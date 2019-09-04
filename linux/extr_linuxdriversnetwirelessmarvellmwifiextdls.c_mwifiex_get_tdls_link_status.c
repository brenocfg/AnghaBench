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
struct mwifiex_sta_node {int tdls_status; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int TDLS_NOT_SETUP ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/  const*) ; 

int mwifiex_get_tdls_link_status(struct mwifiex_private *priv, const u8 *mac)
{
	struct mwifiex_sta_node *sta_ptr;

	sta_ptr = mwifiex_get_sta_entry(priv, mac);
	if (sta_ptr)
		return sta_ptr->tdls_status;

	return TDLS_NOT_SETUP;
}