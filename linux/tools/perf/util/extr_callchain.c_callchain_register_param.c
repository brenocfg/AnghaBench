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
struct callchain_param {int mode; int /*<<< orphan*/  sort; } ;

/* Variables and functions */
#define  CHAIN_FLAT 132 
#define  CHAIN_FOLDED 131 
#define  CHAIN_GRAPH_ABS 130 
#define  CHAIN_GRAPH_REL 129 
#define  CHAIN_NONE 128 
 int /*<<< orphan*/  sort_chain_flat ; 
 int /*<<< orphan*/  sort_chain_graph_abs ; 
 int /*<<< orphan*/  sort_chain_graph_rel ; 

int callchain_register_param(struct callchain_param *param)
{
	switch (param->mode) {
	case CHAIN_GRAPH_ABS:
		param->sort = sort_chain_graph_abs;
		break;
	case CHAIN_GRAPH_REL:
		param->sort = sort_chain_graph_rel;
		break;
	case CHAIN_FLAT:
	case CHAIN_FOLDED:
		param->sort = sort_chain_flat;
		break;
	case CHAIN_NONE:
	default:
		return -1;
	}
	return 0;
}