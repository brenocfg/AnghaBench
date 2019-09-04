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
 int /*<<< orphan*/  helper_extend ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_extend_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_helper_hash ; 

void nf_conntrack_helper_fini(void)
{
	nf_ct_extend_unregister(&helper_extend);
	kvfree(nf_ct_helper_hash);
}