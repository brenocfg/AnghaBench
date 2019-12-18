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
struct aa_ns {int dummy; } ;

/* Variables and functions */
 struct aa_profile* aa_lookupn_profile (struct aa_ns*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct aa_profile *aa_lookup_profile(struct aa_ns *ns, const char *hname)
{
	return aa_lookupn_profile(ns, hname, strlen(hname));
}