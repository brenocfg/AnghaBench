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
struct TYPE_2__ {int flags; } ;
struct aa_profile {TYPE_1__ label; } ;

/* Variables and functions */
 int EEXIST ; 
 int EPERM ; 
 int FLAG_IMMUTIBLE ; 

__attribute__((used)) static int replacement_allowed(struct aa_profile *profile, int noreplace,
			       const char **info)
{
	if (profile) {
		if (profile->label.flags & FLAG_IMMUTIBLE) {
			*info = "cannot replace immutible profile";
			return -EPERM;
		} else if (noreplace) {
			*info = "profile already exists";
			return -EEXIST;
		}
	}
	return 0;
}