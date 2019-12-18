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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ phpdbg_watch_element ;
typedef  int /*<<< orphan*/  Bucket ;

/* Variables and functions */
 int /*<<< orphan*/  PHPDBG_WATCH_SIMPLE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  phpdbg_add_bucket_watch_element (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int phpdbg_create_simple_watchpoint(zval *zv, phpdbg_watch_element *element) {
	element->flags = PHPDBG_WATCH_SIMPLE;
	phpdbg_add_bucket_watch_element((Bucket *) zv, element);
	return SUCCESS;
}