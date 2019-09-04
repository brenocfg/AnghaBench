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
struct xt_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xt_unregister_match (struct xt_match*) ; 

void
xt_unregister_matches(struct xt_match *match, unsigned int n)
{
	while (n-- > 0)
		xt_unregister_match(&match[n]);
}