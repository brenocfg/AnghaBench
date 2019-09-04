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
struct TYPE_2__ {int max_ddbs; int /*<<< orphan*/  ddb_lock; int /*<<< orphan*/  ddb_bitmap; } ;
struct asd_ha_struct {TYPE_1__ hw_prof; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  asd_extend_cmdctx (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_extend_devctx (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_get_max_scb_ddb (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asd_init_ctxmem(struct asd_ha_struct *asd_ha)
{
	int bitmap_bytes;

	asd_get_max_scb_ddb(asd_ha);
	asd_extend_devctx(asd_ha);
	asd_extend_cmdctx(asd_ha);

	/* The kernel wants bitmaps to be unsigned long sized. */
	bitmap_bytes = (asd_ha->hw_prof.max_ddbs+7)/8;
	bitmap_bytes = BITS_TO_LONGS(bitmap_bytes*8)*sizeof(unsigned long);
	asd_ha->hw_prof.ddb_bitmap = kzalloc(bitmap_bytes, GFP_KERNEL);
	if (!asd_ha->hw_prof.ddb_bitmap)
		return -ENOMEM;
	spin_lock_init(&asd_ha->hw_prof.ddb_lock);

	return 0;
}