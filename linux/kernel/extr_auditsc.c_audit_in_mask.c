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
struct audit_krule {int* mask; } ;

/* Variables and functions */
 int AUDIT_BIT (unsigned long) ; 
 int AUDIT_BITMASK_SIZE ; 
 int AUDIT_WORD (unsigned long) ; 

__attribute__((used)) static int audit_in_mask(const struct audit_krule *rule, unsigned long val)
{
	int word, bit;

	if (val > 0xffffffff)
		return false;

	word = AUDIT_WORD(val);
	if (word >= AUDIT_BITMASK_SIZE)
		return false;

	bit = AUDIT_BIT(val);

	return rule->mask[word] & bit;
}