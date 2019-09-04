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

/* Variables and functions */
 int /*<<< orphan*/  NSH_BASE_HDR_LEN ; 
 int /*<<< orphan*/  NSH_CTX_HDRS_MAX_LEN ; 
 size_t nla_total_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ovs_nsh_key_attr_size(void)
{
	/* Whenever adding new OVS_NSH_KEY_ FIELDS, we should consider
	 * updating this function.
	 */
	return  nla_total_size(NSH_BASE_HDR_LEN) /* OVS_NSH_KEY_ATTR_BASE */
		/* OVS_NSH_KEY_ATTR_MD1 and OVS_NSH_KEY_ATTR_MD2 are
		 * mutually exclusive, so the bigger one can cover
		 * the small one.
		 */
		+ nla_total_size(NSH_CTX_HDRS_MAX_LEN);
}