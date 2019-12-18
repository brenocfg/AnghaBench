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
struct state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmt ; 
 scalar_t__ tzload (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct state* const,int) ; 
 int /*<<< orphan*/  tzparse (int /*<<< orphan*/ ,struct state* const,int) ; 

__attribute__((used)) static void
gmtload(struct state *const sp)
{
	if (tzload(gmt, NULL, sp, true) != 0)
		tzparse(gmt, sp, true);
}