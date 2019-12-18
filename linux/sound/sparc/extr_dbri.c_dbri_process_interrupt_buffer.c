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
struct snd_dbri {size_t dbri_irqp; TYPE_1__* dma; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {scalar_t__* intr; } ;

/* Variables and functions */
 size_t DBRI_INT_BLK ; 
 int /*<<< orphan*/  dbri_process_one_interrupt (struct snd_dbri*,scalar_t__) ; 

__attribute__((used)) static void dbri_process_interrupt_buffer(struct snd_dbri *dbri)
{
	s32 x;

	while ((x = dbri->dma->intr[dbri->dbri_irqp]) != 0) {
		dbri->dma->intr[dbri->dbri_irqp] = 0;
		dbri->dbri_irqp++;
		if (dbri->dbri_irqp == DBRI_INT_BLK)
			dbri->dbri_irqp = 1;

		dbri_process_one_interrupt(dbri, x);
	}
}