#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int quiet; } ;
struct lwan {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_use_colors () ; 
 int quiet ; 
 int /*<<< orphan*/  use_colors ; 

void lwan_status_init(struct lwan *l)
{
#ifdef NDEBUG
    quiet = l->config.quiet;
#else
    quiet = false;
    (void)l;
#endif
    use_colors = can_use_colors();
}