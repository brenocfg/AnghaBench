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
typedef  size_t ut8 ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int MCS96_2B ; 
 int MCS96_3B ; 
 int MCS96_4B ; 
 int MCS96_5B ; 
 int MCS96_6B ; 
 TYPE_1__* mcs96_op ; 

__attribute__((used)) static int mcs96_len (const ut8 buf) {
	if (mcs96_op[buf].type & MCS96_6B) {
		return 6;
	}
	if (mcs96_op[buf].type & MCS96_5B) {
		return 5;
	}
	if (mcs96_op[buf].type & MCS96_4B) {
		return 4;
	}
	if (mcs96_op[buf].type & MCS96_3B) {
		return 3;
	}
	if (mcs96_op[buf].type & MCS96_2B) {
		return 2;
	}
	return 1;
}