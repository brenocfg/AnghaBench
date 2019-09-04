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
struct ovs_conntrack_info {scalar_t__ ct; scalar_t__ helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_conntrack_helper_put (scalar_t__) ; 
 int /*<<< orphan*/  nf_ct_tmpl_free (scalar_t__) ; 

__attribute__((used)) static void __ovs_ct_free_action(struct ovs_conntrack_info *ct_info)
{
	if (ct_info->helper)
		nf_conntrack_helper_put(ct_info->helper);
	if (ct_info->ct)
		nf_ct_tmpl_free(ct_info->ct);
}