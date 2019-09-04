#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int d_last; int d_next; } ;
struct ast_vhub_ep {TYPE_1__ epn; } ;

/* Variables and functions */
 int AST_VHUB_DESCS_COUNT ; 

__attribute__((used)) static inline unsigned int ast_vhub_count_free_descs(struct ast_vhub_ep *ep)
{
	/*
	 * d_next == d_last means descriptor list empty to HW,
	 * thus we can only have AST_VHUB_DESCS_COUNT-1 descriptors
	 * in the list
	 */
	return (ep->epn.d_last + AST_VHUB_DESCS_COUNT - ep->epn.d_next - 1) &
		(AST_VHUB_DESCS_COUNT - 1);
}