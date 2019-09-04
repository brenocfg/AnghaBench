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
typedef  int u16 ;
struct cpcap_coulomb_counter_data {int sample; int accumulator; int offset; } ;
struct cpcap_battery_ddata {int /*<<< orphan*/  reg; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CPCAP_REG_CCS1 ; 
 int cpcap_battery_cc_to_uah (struct cpcap_battery_ddata*,int,int,int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpcap_battery_read_accumulated(struct cpcap_battery_ddata *ddata,
			       struct cpcap_coulomb_counter_data *ccd)
{
	u16 buf[7];	/* CPCAP_REG_CC1 to CCI */
	int error;

	ccd->sample = 0;
	ccd->accumulator = 0;
	ccd->offset = 0;

	/* Read coulomb counter register range */
	error = regmap_bulk_read(ddata->reg, CPCAP_REG_CCS1,
				 buf, ARRAY_SIZE(buf));
	if (error)
		return 0;

	/* Sample value CPCAP_REG_CCS1 & 2 */
	ccd->sample = (buf[1] & 0x0fff) << 16;
	ccd->sample |= buf[0];

	/* Accumulator value CPCAP_REG_CCA1 & 2 */
	ccd->accumulator = ((s16)buf[3]) << 16;
	ccd->accumulator |= buf[2];

	/* Offset value CPCAP_REG_CCO */
	ccd->offset = buf[5];

	/* Adjust offset based on mode value CPCAP_REG_CCM? */
	if (buf[4] >= 0x200)
		ccd->offset |= 0xfc00;

	return cpcap_battery_cc_to_uah(ddata,
				       ccd->sample,
				       ccd->accumulator,
				       ccd->offset);
}