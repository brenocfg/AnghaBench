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
struct TYPE_2__ {int /*<<< orphan*/  sym; } ;
struct hist_entry {TYPE_1__ ms; } ;

/* Variables and functions */
 int _hist_entry__sym_size_snprintf (int /*<<< orphan*/ ,char*,size_t,unsigned int) ; 

__attribute__((used)) static int hist_entry__sym_size_snprintf(struct hist_entry *he, char *bf,
					 size_t size, unsigned int width)
{
	return _hist_entry__sym_size_snprintf(he->ms.sym, bf, size, width);
}