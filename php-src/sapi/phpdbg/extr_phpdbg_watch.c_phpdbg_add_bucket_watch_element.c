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
typedef  int /*<<< orphan*/  phpdbg_watchpoint_t ;
typedef  int /*<<< orphan*/  phpdbg_watch_element ;
typedef  int /*<<< orphan*/  Bucket ;

/* Variables and functions */
 int /*<<< orphan*/ * phpdbg_add_watch_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phpdbg_set_bucket_watchpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phpdbg_watch_parent_ht (int /*<<< orphan*/ *) ; 

phpdbg_watch_element *phpdbg_add_bucket_watch_element(Bucket *bucket, phpdbg_watch_element *element) {
	phpdbg_watchpoint_t watch;
	phpdbg_set_bucket_watchpoint(bucket, &watch);
	element = phpdbg_add_watch_element(&watch, element);
	phpdbg_watch_parent_ht(element);
	return element;
}