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
struct TYPE_2__ {unsigned int* start; int /*<<< orphan*/  dfa; } ;
struct aa_profile {TYPE_1__ policy; } ;

/* Variables and functions */
 unsigned char AA_CLASS_LAST ; 
 unsigned int aa_dfa_match_len (int /*<<< orphan*/ ,unsigned int,unsigned char*,int) ; 

__attribute__((used)) static inline unsigned int PROFILE_MEDIATES(struct aa_profile *profile,
					    unsigned char class)
{
	if (class <= AA_CLASS_LAST)
		return profile->policy.start[class];
	else
		return aa_dfa_match_len(profile->policy.dfa,
					profile->policy.start[0], &class, 1);
}