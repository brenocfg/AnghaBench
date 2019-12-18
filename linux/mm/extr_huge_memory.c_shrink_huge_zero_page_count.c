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
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;

/* Variables and functions */
 unsigned long HPAGE_PMD_NR ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_zero_refcount ; 

__attribute__((used)) static unsigned long shrink_huge_zero_page_count(struct shrinker *shrink,
					struct shrink_control *sc)
{
	/* we can free zero page only if last reference remains */
	return atomic_read(&huge_zero_refcount) == 1 ? HPAGE_PMD_NR : 0;
}