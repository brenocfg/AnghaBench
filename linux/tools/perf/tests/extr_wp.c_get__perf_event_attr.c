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
struct perf_event_attr {int size; int bp_type; unsigned long bp_addr; unsigned long bp_len; int sample_period; int exclude_kernel; int exclude_hv; int /*<<< orphan*/  sample_type; scalar_t__ config; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_SAMPLE_IP ; 
 int /*<<< orphan*/  PERF_TYPE_BREAKPOINT ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void get__perf_event_attr(struct perf_event_attr *attr, int wp_type,
				 void *wp_addr, unsigned long wp_len)
{
	memset(attr, 0, sizeof(struct perf_event_attr));
	attr->type           = PERF_TYPE_BREAKPOINT;
	attr->size           = sizeof(struct perf_event_attr);
	attr->config         = 0;
	attr->bp_type        = wp_type;
	attr->bp_addr        = (unsigned long)wp_addr;
	attr->bp_len         = wp_len;
	attr->sample_period  = 1;
	attr->sample_type    = PERF_SAMPLE_IP;
	attr->exclude_kernel = 1;
	attr->exclude_hv     = 1;
}