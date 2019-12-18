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
struct dccp_ackvec {int /*<<< orphan*/  av_records; scalar_t__ av_buf_tail; scalar_t__ av_buf_head; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ DCCPAV_MAX_ACKVEC_LEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_ackvec_slab ; 
 struct dccp_ackvec* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

struct dccp_ackvec *dccp_ackvec_alloc(const gfp_t priority)
{
	struct dccp_ackvec *av = kmem_cache_zalloc(dccp_ackvec_slab, priority);

	if (av != NULL) {
		av->av_buf_head	= av->av_buf_tail = DCCPAV_MAX_ACKVEC_LEN - 1;
		INIT_LIST_HEAD(&av->av_records);
	}
	return av;
}