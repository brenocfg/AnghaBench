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
struct TYPE_2__ {int /*<<< orphan*/  nodes; int /*<<< orphan*/  preferred_node; } ;
struct mempolicy {int flags; unsigned short mode; TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
#define  MPOL_BIND 131 
#define  MPOL_DEFAULT 130 
 unsigned short MPOL_F_LOCAL ; 
 int MPOL_F_MORON ; 
 unsigned short MPOL_F_RELATIVE_NODES ; 
 unsigned short MPOL_F_STATIC_NODES ; 
#define  MPOL_INTERLEAVE 129 
 unsigned short MPOL_LOCAL ; 
 unsigned short MPOL_MODE_FLAGS ; 
#define  MPOL_PREFERRED 128 
 int /*<<< orphan*/  NODE_MASK_NONE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct mempolicy default_policy ; 
 int /*<<< orphan*/  node_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodemask_pr_args (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodes_empty (int /*<<< orphan*/ ) ; 
 char** policy_modes ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

void mpol_to_str(char *buffer, int maxlen, struct mempolicy *pol)
{
	char *p = buffer;
	nodemask_t nodes = NODE_MASK_NONE;
	unsigned short mode = MPOL_DEFAULT;
	unsigned short flags = 0;

	if (pol && pol != &default_policy && !(pol->flags & MPOL_F_MORON)) {
		mode = pol->mode;
		flags = pol->flags;
	}

	switch (mode) {
	case MPOL_DEFAULT:
		break;
	case MPOL_PREFERRED:
		if (flags & MPOL_F_LOCAL)
			mode = MPOL_LOCAL;
		else
			node_set(pol->v.preferred_node, nodes);
		break;
	case MPOL_BIND:
	case MPOL_INTERLEAVE:
		nodes = pol->v.nodes;
		break;
	default:
		WARN_ON_ONCE(1);
		snprintf(p, maxlen, "unknown");
		return;
	}

	p += snprintf(p, maxlen, "%s", policy_modes[mode]);

	if (flags & MPOL_MODE_FLAGS) {
		p += snprintf(p, buffer + maxlen - p, "=");

		/*
		 * Currently, the only defined flags are mutually exclusive
		 */
		if (flags & MPOL_F_STATIC_NODES)
			p += snprintf(p, buffer + maxlen - p, "static");
		else if (flags & MPOL_F_RELATIVE_NODES)
			p += snprintf(p, buffer + maxlen - p, "relative");
	}

	if (!nodes_empty(nodes))
		p += scnprintf(p, buffer + maxlen - p, ":%*pbl",
			       nodemask_pr_args(&nodes));
}