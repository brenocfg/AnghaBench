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
struct key_tag {int removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_put_tag (struct key_tag*) ; 
 int /*<<< orphan*/  key_schedule_gc_links () ; 

void key_remove_domain(struct key_tag *domain_tag)
{
	domain_tag->removed = true;
	if (!key_put_tag(domain_tag))
		key_schedule_gc_links();
}