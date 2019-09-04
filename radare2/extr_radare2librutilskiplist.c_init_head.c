#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__** forward; } ;
typedef  TYPE_1__ RSkipListNode ;

/* Variables and functions */
 int SKIPLIST_MAX_DEPTH ; 

__attribute__((used)) static void init_head (RSkipListNode *head) {
	int i;
	for (i = 0; i <= SKIPLIST_MAX_DEPTH; i++) {
		head->forward[i] = head;
	}
}