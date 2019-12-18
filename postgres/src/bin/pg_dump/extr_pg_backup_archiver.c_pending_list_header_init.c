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
struct TYPE_3__ {struct TYPE_3__* pending_next; struct TYPE_3__* pending_prev; } ;
typedef  TYPE_1__ TocEntry ;

/* Variables and functions */

__attribute__((used)) static void
pending_list_header_init(TocEntry *l)
{
	l->pending_prev = l->pending_next = l;
}