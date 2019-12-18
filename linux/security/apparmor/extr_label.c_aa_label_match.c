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
typedef  int /*<<< orphan*/  u32 ;
struct aa_profile {int dummy; } ;
struct aa_perms {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_perms allperms ; 
 int label_components_match (struct aa_profile*,struct aa_label*,unsigned int,int,int /*<<< orphan*/ ,struct aa_perms*) ; 
 int label_compound_match (struct aa_profile*,struct aa_label*,unsigned int,int,int /*<<< orphan*/ ,struct aa_perms*) ; 

int aa_label_match(struct aa_profile *profile, struct aa_label *label,
		   unsigned int state, bool subns, u32 request,
		   struct aa_perms *perms)
{
	int error = label_compound_match(profile, label, state, subns, request,
					 perms);
	if (!error)
		return error;

	*perms = allperms;
	return label_components_match(profile, label, state, subns, request,
				      perms);
}