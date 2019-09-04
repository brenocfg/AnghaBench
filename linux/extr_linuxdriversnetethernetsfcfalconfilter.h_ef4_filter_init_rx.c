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
struct ef4_filter_spec {int priority; int flags; unsigned int dmaq_id; int /*<<< orphan*/  rss_context; } ;
typedef  enum ef4_filter_priority { ____Placeholder_ef4_filter_priority } ef4_filter_priority ;
typedef  enum ef4_filter_flags { ____Placeholder_ef4_filter_flags } ef4_filter_flags ;

/* Variables and functions */
 int EF4_FILTER_FLAG_RX ; 
 int /*<<< orphan*/  EF4_FILTER_RSS_CONTEXT_DEFAULT ; 
 int /*<<< orphan*/  memset (struct ef4_filter_spec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ef4_filter_init_rx(struct ef4_filter_spec *spec,
				      enum ef4_filter_priority priority,
				      enum ef4_filter_flags flags,
				      unsigned rxq_id)
{
	memset(spec, 0, sizeof(*spec));
	spec->priority = priority;
	spec->flags = EF4_FILTER_FLAG_RX | flags;
	spec->rss_context = EF4_FILTER_RSS_CONTEXT_DEFAULT;
	spec->dmaq_id = rxq_id;
}