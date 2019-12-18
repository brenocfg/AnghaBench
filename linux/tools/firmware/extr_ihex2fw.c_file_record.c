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
struct ihex_binrec {scalar_t__ addr; struct ihex_binrec* next; } ;

/* Variables and functions */
 struct ihex_binrec* records ; 
 int /*<<< orphan*/  sort_records ; 

__attribute__((used)) static void file_record(struct ihex_binrec *record)
{
	struct ihex_binrec **p = &records;

	while ((*p) && (!sort_records || (*p)->addr < record->addr))
		p = &((*p)->next);

	record->next = *p;
	*p = record;
}