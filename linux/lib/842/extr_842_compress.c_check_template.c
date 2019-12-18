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
typedef  size_t u8 ;
struct sw842_param {int dummy; } ;

/* Variables and functions */
 size_t OPS_MAX ; 
 size_t OP_ACTION_INDEX ; 
 size_t OP_AMOUNT ; 
 size_t OP_AMOUNT_2 ; 
 size_t OP_AMOUNT_4 ; 
 size_t OP_AMOUNT_8 ; 
 int check_index (struct sw842_param*,int,int) ; 
 size_t** comp_ops ; 

__attribute__((used)) static bool check_template(struct sw842_param *p, u8 c)
{
	u8 *t = comp_ops[c];
	int i, match, b = 0;

	if (c >= OPS_MAX)
		return false;

	for (i = 0; i < 4; i++) {
		if (t[i] & OP_ACTION_INDEX) {
			if (t[i] & OP_AMOUNT_2)
				match = check_index(p, 2, b >> 1);
			else if (t[i] & OP_AMOUNT_4)
				match = check_index(p, 4, b >> 2);
			else if (t[i] & OP_AMOUNT_8)
				match = check_index(p, 8, 0);
			else
				return false;
			if (!match)
				return false;
		}

		b += t[i] & OP_AMOUNT;
	}

	return true;
}