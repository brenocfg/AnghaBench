#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* hname; } ;
struct TYPE_3__ {int /*<<< orphan*/  dfa; } ;
struct aa_profile {scalar_t__ ns; TYPE_2__ base; TYPE_1__ file; } ;

/* Variables and functions */
 unsigned int aa_dfa_match (int /*<<< orphan*/ ,unsigned int,char const*) ; 
 unsigned int aa_dfa_match_len (int /*<<< orphan*/ ,unsigned int,char*,int) ; 
 char* aa_ns_name (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static inline unsigned int match_component(struct aa_profile *profile,
					   struct aa_profile *tp,
					   bool stack, unsigned int state)
{
	const char *ns_name;

	if (stack)
		state = aa_dfa_match(profile->file.dfa, state, "&");
	if (profile->ns == tp->ns)
		return aa_dfa_match(profile->file.dfa, state, tp->base.hname);

	/* try matching with namespace name and then profile */
	ns_name = aa_ns_name(profile->ns, tp->ns, true);
	state = aa_dfa_match_len(profile->file.dfa, state, ":", 1);
	state = aa_dfa_match(profile->file.dfa, state, ns_name);
	state = aa_dfa_match_len(profile->file.dfa, state, ":", 1);
	return aa_dfa_match(profile->file.dfa, state, tp->base.hname);
}