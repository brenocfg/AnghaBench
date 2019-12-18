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
struct page_pool {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,scalar_t__) ; 
 scalar_t__ page_pool_inflight (struct page_pool*) ; 

__attribute__((used)) static bool __page_pool_safe_to_destroy(struct page_pool *pool)
{
	s32 inflight = page_pool_inflight(pool);

	/* The distance should not be able to become negative */
	WARN(inflight < 0, "Negative(%d) inflight packet-pages", inflight);

	return (inflight == 0);
}