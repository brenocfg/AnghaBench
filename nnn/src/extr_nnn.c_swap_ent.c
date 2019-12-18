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
struct entry {int dummy; } ;

/* Variables and functions */
 struct entry* dents ; 

__attribute__((used)) static inline void swap_ent(int id1, int id2)
{
	struct entry _dent, *pdent1 = &dents[id1], *pdent2 =  &dents[id2];

	*(&_dent) = *pdent1;
	*pdent1 = *pdent2;
	*pdent2 = *(&_dent);
}