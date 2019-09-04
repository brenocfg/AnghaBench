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
struct dst_entry {int dummy; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_uncached; struct dst_entry dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dst_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt6_info_init(struct rt6_info *rt)
{
	struct dst_entry *dst = &rt->dst;

	memset(dst + 1, 0, sizeof(*rt) - sizeof(*dst));
	INIT_LIST_HEAD(&rt->rt6i_uncached);
}