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
typedef  scalar_t__ u16 ;
struct reg_dmn_pair_mapping {scalar_t__ reg_domain; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_dmn_pair_mapping*) ; 
 scalar_t__ NO_ENUMRD ; 
 struct reg_dmn_pair_mapping* regDomainPairs ; 

__attribute__((used)) static struct reg_dmn_pair_mapping *
ath6kl_get_regpair(u16 regdmn)
{
	int i;

	if (regdmn == NO_ENUMRD)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(regDomainPairs); i++) {
		if (regDomainPairs[i].reg_domain == regdmn)
			return &regDomainPairs[i];
	}

	return NULL;
}