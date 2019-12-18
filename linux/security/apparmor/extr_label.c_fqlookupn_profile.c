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
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_profile* aa_fqlookupn_profile (struct aa_label*,char const*,size_t) ; 
 char* skipn_spaces (char const*,size_t) ; 

__attribute__((used)) static struct aa_profile *fqlookupn_profile(struct aa_label *base,
					    struct aa_label *currentbase,
					    const char *str, size_t n)
{
	const char *first = skipn_spaces(str, n);

	if (first && *first == ':')
		return aa_fqlookupn_profile(base, str, n);

	return aa_fqlookupn_profile(currentbase, str, n);
}