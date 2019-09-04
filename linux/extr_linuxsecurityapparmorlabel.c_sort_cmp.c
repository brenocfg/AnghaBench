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
struct aa_profile {int dummy; } ;

/* Variables and functions */
 int profile_cmp (struct aa_profile*,struct aa_profile*) ; 

__attribute__((used)) static int sort_cmp(const void *a, const void *b)
{
	return profile_cmp(*(struct aa_profile **)a, *(struct aa_profile **)b);
}