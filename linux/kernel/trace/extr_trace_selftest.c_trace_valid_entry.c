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
struct trace_entry {int type; } ;

/* Variables and functions */
#define  TRACE_BRANCH 135 
#define  TRACE_CTX 134 
#define  TRACE_FN 133 
#define  TRACE_GRAPH_ENT 132 
#define  TRACE_GRAPH_RET 131 
#define  TRACE_PRINT 130 
#define  TRACE_STACK 129 
#define  TRACE_WAKE 128 

__attribute__((used)) static inline int trace_valid_entry(struct trace_entry *entry)
{
	switch (entry->type) {
	case TRACE_FN:
	case TRACE_CTX:
	case TRACE_WAKE:
	case TRACE_STACK:
	case TRACE_PRINT:
	case TRACE_BRANCH:
	case TRACE_GRAPH_ENT:
	case TRACE_GRAPH_RET:
		return 1;
	}
	return 0;
}