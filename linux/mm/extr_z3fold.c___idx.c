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
struct z3fold_header {int first_num; } ;
typedef  enum buddy { ____Placeholder_buddy } buddy ;

/* Variables and functions */
 int BUDDY_MASK ; 

__attribute__((used)) static inline int __idx(struct z3fold_header *zhdr, enum buddy bud)
{
	return (bud + zhdr->first_num) & BUDDY_MASK;
}