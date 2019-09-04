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
struct TYPE_4__ {scalar_t__ fd; struct TYPE_4__* prev; scalar_t__ line_num; } ;
typedef  TYPE_1__ BufferedFile ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 TYPE_1__* file ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  total_lines ; 

void tcc_close(void)
{
	BufferedFile *bf = file;
	if (bf->fd > 0) {
		close (bf->fd);
		total_lines += bf->line_num;
	}
	file = bf->prev;
	free (bf);
}