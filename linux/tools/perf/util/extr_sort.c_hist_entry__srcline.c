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
struct TYPE_2__ {int /*<<< orphan*/  sym; int /*<<< orphan*/  map; } ;
struct hist_entry {TYPE_1__ ms; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 char* map__srcline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *hist_entry__srcline(struct hist_entry *he)
{
	return map__srcline(he->ms.map, he->ip, he->ms.sym);
}