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
struct fsnotify_mark {int dummy; } ;
struct audit_chunk {int dummy; } ;
struct TYPE_2__ {struct audit_chunk* chunk; } ;

/* Variables and functions */
 TYPE_1__* audit_mark (struct fsnotify_mark*) ; 

__attribute__((used)) static struct audit_chunk *mark_chunk(struct fsnotify_mark *mark)
{
	return audit_mark(mark)->chunk;
}