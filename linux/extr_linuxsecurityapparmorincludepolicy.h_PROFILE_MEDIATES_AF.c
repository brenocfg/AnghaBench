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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dfa; } ;
struct aa_profile {TYPE_1__ policy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AA_CLASS_NET ; 
 unsigned int PROFILE_MEDIATES (struct aa_profile*,int /*<<< orphan*/ ) ; 
 unsigned int aa_dfa_match_len (int /*<<< orphan*/ ,unsigned int,char*,int) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int PROFILE_MEDIATES_AF(struct aa_profile *profile,
					       u16 AF) {
	unsigned int state = PROFILE_MEDIATES(profile, AA_CLASS_NET);
	__be16 be_af = cpu_to_be16(AF);

	if (!state)
		return 0;
	return aa_dfa_match_len(profile->policy.dfa, state, (char *) &be_af, 2);
}