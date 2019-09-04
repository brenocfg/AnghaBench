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
struct addr_filter {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct addr_filter* zalloc (int) ; 

__attribute__((used)) static struct addr_filter *addr_filter__new(void)
{
	struct addr_filter *filt = zalloc(sizeof(*filt));

	if (filt)
		INIT_LIST_HEAD(&filt->list);

	return filt;
}