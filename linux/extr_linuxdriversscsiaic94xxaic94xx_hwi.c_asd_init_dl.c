#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct done_list_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dl_tasklet; scalar_t__ dl_next; int /*<<< orphan*/  dl_toggle; TYPE_2__* actual_dl; int /*<<< orphan*/  dl; } ;
struct asd_ha_struct {TYPE_1__ seq; } ;
struct TYPE_4__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DEF_DL_TOGGLE ; 
 int ASD_DL_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* asd_alloc_coherent (struct asd_ha_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_dl_tasklet_handler ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int asd_init_dl(struct asd_ha_struct *asd_ha)
{
	asd_ha->seq.actual_dl
		= asd_alloc_coherent(asd_ha,
			     ASD_DL_SIZE * sizeof(struct done_list_struct),
				     GFP_KERNEL);
	if (!asd_ha->seq.actual_dl)
		return -ENOMEM;
	asd_ha->seq.dl = asd_ha->seq.actual_dl->vaddr;
	asd_ha->seq.dl_toggle = ASD_DEF_DL_TOGGLE;
	asd_ha->seq.dl_next = 0;
	tasklet_init(&asd_ha->seq.dl_tasklet, asd_dl_tasklet_handler,
		     (unsigned long) asd_ha);

	return 0;
}