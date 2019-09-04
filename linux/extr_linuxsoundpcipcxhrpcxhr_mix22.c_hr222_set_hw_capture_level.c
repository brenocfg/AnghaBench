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
struct pcxhr_mgr {int /*<<< orphan*/  capture_chips; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCXHR_DATA_CODEC ; 
 int /*<<< orphan*/  PCXHR_INPB (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_XLX_DATA ; 
 int /*<<< orphan*/  PCXHR_XLX_RUER ; 

__attribute__((used)) static int hr222_set_hw_capture_level(struct pcxhr_mgr *mgr,
				      int level_l, int level_r, int level_mic)
{
	/* program all input levels at the same time */
	unsigned int data;
	int i;

	if (!mgr->capture_chips)
		return -EINVAL;	/* no PCX22 */

	data  = ((level_mic & 0xff) << 24);	/* micro is mono, but apply */
	data |= ((level_mic & 0xff) << 16);	/* level on both channels */
	data |= ((level_r & 0xff) << 8);	/* line input right channel */
	data |= (level_l & 0xff);		/* line input left channel */

	PCXHR_INPB(mgr, PCXHR_XLX_DATA);	/* activate input codec */
	/* send 32 bits (4 x 8 bits) */
	for (i = 0; i < 32; i++, data <<= 1) {
		PCXHR_OUTPB(mgr, PCXHR_XLX_DATA,
			    (data & 0x80000000) ? PCXHR_DATA_CODEC : 0);
	}
	PCXHR_INPB(mgr, PCXHR_XLX_RUER);	/* close input level codec */
	return 0;
}