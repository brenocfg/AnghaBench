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
struct clocksource {int rating; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  clocksource_enqueue (struct clocksource*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __clocksource_change_rating(struct clocksource *cs, int rating)
{
	list_del(&cs->list);
	cs->rating = rating;
	clocksource_enqueue(cs);
}