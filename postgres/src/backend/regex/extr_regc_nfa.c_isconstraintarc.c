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
struct arc {int type; } ;

/* Variables and functions */
#define  AHEAD 130 
#define  BEHIND 129 
#define  LACON 128 

__attribute__((used)) static inline int
isconstraintarc(struct arc *a)
{
	switch (a->type)
	{
		case '^':
		case '$':
		case BEHIND:
		case AHEAD:
		case LACON:
			return 1;
	}
	return 0;
}