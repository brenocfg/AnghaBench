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
struct TYPE_2__ {int /*<<< orphan*/  bbs; } ;
typedef  TYPE_1__ RAnalFunction ;

/* Variables and functions */
 scalar_t__ r_list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmpbbs (const void *_a, const void *_b) {
	const RAnalFunction *a = _a, *b = _b;
	int la = (int)r_list_length (a->bbs);
	int lb = (int)r_list_length (b->bbs);
	return (la > lb)? -1: (la < lb)? 1 : 0;
}