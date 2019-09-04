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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {void* key; scalar_t__ done; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 TYPE_1__* map_iter (struct seq_file*) ; 

__attribute__((used)) static void *map_seq_start(struct seq_file *m, loff_t *pos)
{
	if (map_iter(m)->done)
		return NULL;

	return *pos ? map_iter(m)->key : SEQ_START_TOKEN;
}