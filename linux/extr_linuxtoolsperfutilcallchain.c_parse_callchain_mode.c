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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_FLAT ; 
 int /*<<< orphan*/  CHAIN_FOLDED ; 
 int /*<<< orphan*/  CHAIN_GRAPH_ABS ; 
 int /*<<< orphan*/  CHAIN_GRAPH_REL ; 
 TYPE_1__ callchain_param ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_callchain_mode(const char *value)
{
	if (!strncmp(value, "graph", strlen(value))) {
		callchain_param.mode = CHAIN_GRAPH_ABS;
		return 0;
	}
	if (!strncmp(value, "flat", strlen(value))) {
		callchain_param.mode = CHAIN_FLAT;
		return 0;
	}
	if (!strncmp(value, "fractal", strlen(value))) {
		callchain_param.mode = CHAIN_GRAPH_REL;
		return 0;
	}
	if (!strncmp(value, "folded", strlen(value))) {
		callchain_param.mode = CHAIN_FOLDED;
		return 0;
	}
	return -1;
}