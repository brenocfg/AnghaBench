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
struct page {int dummy; } ;
struct alloc_context {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum compact_result { ____Placeholder_compact_result } compact_result ;
typedef  enum compact_priority { ____Placeholder_compact_priority } compact_priority ;

/* Variables and functions */
 int COMPACT_SKIPPED ; 

__attribute__((used)) static inline struct page *
__alloc_pages_direct_compact(gfp_t gfp_mask, unsigned int order,
		unsigned int alloc_flags, const struct alloc_context *ac,
		enum compact_priority prio, enum compact_result *compact_result)
{
	*compact_result = COMPACT_SKIPPED;
	return NULL;
}