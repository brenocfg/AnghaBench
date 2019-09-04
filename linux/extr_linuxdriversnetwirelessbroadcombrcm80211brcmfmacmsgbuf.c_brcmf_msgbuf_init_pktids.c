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
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_msgbuf_pktids {int /*<<< orphan*/  array_size; struct brcmf_msgbuf_pktid* array; } ;
struct brcmf_msgbuf_pktid {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct brcmf_msgbuf_pktid* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct brcmf_msgbuf_pktid*) ; 
 struct brcmf_msgbuf_pktids* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct brcmf_msgbuf_pktids *
brcmf_msgbuf_init_pktids(u32 nr_array_entries,
			 enum dma_data_direction direction)
{
	struct brcmf_msgbuf_pktid *array;
	struct brcmf_msgbuf_pktids *pktids;

	array = kcalloc(nr_array_entries, sizeof(*array), GFP_KERNEL);
	if (!array)
		return NULL;

	pktids = kzalloc(sizeof(*pktids), GFP_KERNEL);
	if (!pktids) {
		kfree(array);
		return NULL;
	}
	pktids->array = array;
	pktids->array_size = nr_array_entries;

	return pktids;
}