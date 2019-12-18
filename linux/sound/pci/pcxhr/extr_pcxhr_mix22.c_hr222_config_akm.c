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
struct pcxhr_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_DATA_CODEC ; 
 int /*<<< orphan*/  PCXHR_INPB (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_XLX_DATA ; 
 int /*<<< orphan*/  PCXHR_XLX_HIFREQ ; 
 int /*<<< orphan*/  PCXHR_XLX_RUER ; 

__attribute__((used)) static void hr222_config_akm(struct pcxhr_mgr *mgr, unsigned short data)
{
	unsigned short mask = 0x8000;
	/* activate access to codec registers */
	PCXHR_INPB(mgr, PCXHR_XLX_HIFREQ);

	while (mask) {
		PCXHR_OUTPB(mgr, PCXHR_XLX_DATA,
			    data & mask ? PCXHR_DATA_CODEC : 0);
		mask >>= 1;
	}
	/* termiate access to codec registers */
	PCXHR_INPB(mgr, PCXHR_XLX_RUER);
}