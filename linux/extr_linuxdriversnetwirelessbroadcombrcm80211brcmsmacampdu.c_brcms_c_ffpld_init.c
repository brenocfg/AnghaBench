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
struct brcms_fifo_info {int* mcs2ampdu_table; scalar_t__ accum_txfunfl; scalar_t__ prev_txfunfl; scalar_t__ accum_txampdu; scalar_t__ dmaxferrate; scalar_t__ ampdu_pld_size; } ;
struct ampdu_info {struct brcms_fifo_info* fifo_tb; } ;

/* Variables and functions */
 int FFPLD_MAX_MCS ; 
 int NUM_FFPLD_FIFO ; 

__attribute__((used)) static void brcms_c_ffpld_init(struct ampdu_info *ampdu)
{
	int i, j;
	struct brcms_fifo_info *fifo;

	for (j = 0; j < NUM_FFPLD_FIFO; j++) {
		fifo = (ampdu->fifo_tb + j);
		fifo->ampdu_pld_size = 0;
		for (i = 0; i <= FFPLD_MAX_MCS; i++)
			fifo->mcs2ampdu_table[i] = 255;
		fifo->dmaxferrate = 0;
		fifo->accum_txampdu = 0;
		fifo->prev_txfunfl = 0;
		fifo->accum_txfunfl = 0;

	}
}