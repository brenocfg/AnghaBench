#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; } ;
struct TYPE_5__ {TYPE_1__ stack; } ;
typedef  TYPE_2__ zend_worklist ;

/* Variables and functions */

__attribute__((used)) static inline int zend_worklist_len(zend_worklist *worklist)
{
	return worklist->stack.len;
}