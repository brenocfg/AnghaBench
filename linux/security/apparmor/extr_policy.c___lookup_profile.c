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
struct aa_policy {int dummy; } ;

/* Variables and functions */
 struct aa_profile* __lookupn_profile (struct aa_policy*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct aa_profile *__lookup_profile(struct aa_policy *base,
					   const char *hname)
{
	return __lookupn_profile(base, hname, strlen(hname));
}