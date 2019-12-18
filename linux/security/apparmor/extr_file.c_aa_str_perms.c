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
struct path_cond {int dummy; } ;
struct aa_perms {int dummy; } ;
struct aa_dfa {int dummy; } ;

/* Variables and functions */
 struct aa_perms aa_compute_fperms (struct aa_dfa*,unsigned int,struct path_cond*) ; 
 unsigned int aa_dfa_match (struct aa_dfa*,unsigned int,char const*) ; 

unsigned int aa_str_perms(struct aa_dfa *dfa, unsigned int start,
			  const char *name, struct path_cond *cond,
			  struct aa_perms *perms)
{
	unsigned int state;
	state = aa_dfa_match(dfa, start, name);
	*perms = aa_compute_fperms(dfa, state, cond);

	return state;
}