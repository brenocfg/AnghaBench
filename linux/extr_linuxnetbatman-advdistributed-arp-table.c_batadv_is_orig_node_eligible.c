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
struct batadv_orig_node {int /*<<< orphan*/  orig; int /*<<< orphan*/  capabilities; } ;
struct batadv_dat_candidate {struct batadv_orig_node* orig_node; } ;
typedef  scalar_t__ batadv_dat_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ORIG_CAPA_HAS_DAT ; 
 scalar_t__ batadv_compare_eth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool batadv_is_orig_node_eligible(struct batadv_dat_candidate *res,
					 int select, batadv_dat_addr_t tmp_max,
					 batadv_dat_addr_t max,
					 batadv_dat_addr_t last_max,
					 struct batadv_orig_node *candidate,
					 struct batadv_orig_node *max_orig_node)
{
	bool ret = false;
	int j;

	/* check if orig node candidate is running DAT */
	if (!test_bit(BATADV_ORIG_CAPA_HAS_DAT, &candidate->capabilities))
		goto out;

	/* Check if this node has already been selected... */
	for (j = 0; j < select; j++)
		if (res[j].orig_node == candidate)
			break;
	/* ..and possibly skip it */
	if (j < select)
		goto out;
	/* sanity check: has it already been selected? This should not happen */
	if (tmp_max > last_max)
		goto out;
	/* check if during this iteration an originator with a closer dht
	 * address has already been found
	 */
	if (tmp_max < max)
		goto out;
	/* this is an hash collision with the temporary selected node. Choose
	 * the one with the lowest address
	 */
	if (tmp_max == max && max_orig_node &&
	    batadv_compare_eth(candidate->orig, max_orig_node->orig))
		goto out;

	ret = true;
out:
	return ret;
}