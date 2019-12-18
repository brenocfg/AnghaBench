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
struct ip_vs_app {int /*<<< orphan*/  app; int /*<<< orphan*/  usecnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_app_put (int /*<<< orphan*/ ) ; 

void ip_vs_app_inc_put(struct ip_vs_app *inc)
{
	atomic_dec(&inc->usecnt);
	ip_vs_app_put(inc->app);
}