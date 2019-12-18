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
typedef  int /*<<< orphan*/  u16 ;
struct snd_m3 {int dummy; } ;
struct m3_list {int curlen; scalar_t__ mem_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMTYPE_INTERNAL_DATA ; 
 int /*<<< orphan*/  snd_m3_assp_read (struct snd_m3*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_m3_assp_write (struct snd_m3*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_m3_remove_list(struct snd_m3 *chip, struct m3_list *list, int index)
{
	u16  val;
	int lastindex = list->curlen - 1;

	if (index != lastindex) {
		val = snd_m3_assp_read(chip, MEMTYPE_INTERNAL_DATA,
				       list->mem_addr + lastindex);
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
				  list->mem_addr + index,
				  val);
	}

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  list->mem_addr + lastindex,
			  0);

	list->curlen--;
}