#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ phpdbg_watchpoint_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int HT_WATCH_OFFSET ; 
 int /*<<< orphan*/  WATCH_ON_HASHTABLE ; 
 int /*<<< orphan*/  phpdbg_set_addr_watchpoint (char*,int,TYPE_1__*) ; 

void phpdbg_set_ht_watchpoint(HashTable *ht, phpdbg_watchpoint_t *watch) {
	phpdbg_set_addr_watchpoint(((char *) ht) + HT_WATCH_OFFSET, sizeof(HashTable) - HT_WATCH_OFFSET, watch);
	watch->type = WATCH_ON_HASHTABLE;
}