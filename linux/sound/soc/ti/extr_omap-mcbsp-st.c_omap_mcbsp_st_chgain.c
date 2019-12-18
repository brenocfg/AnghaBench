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
struct omap_mcbsp_st_data {int /*<<< orphan*/  ch1gain; int /*<<< orphan*/  ch0gain; } ;
struct omap_mcbsp {struct omap_mcbsp_st_data* st_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCBSP_ST_READ (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCBSP_ST_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SGAINCR ; 
 int /*<<< orphan*/  SSELCR ; 
 int ST_CH0GAIN (int /*<<< orphan*/ ) ; 
 int ST_CH1GAIN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_mcbsp_st_chgain(struct omap_mcbsp *mcbsp)
{
	u16 w;
	struct omap_mcbsp_st_data *st_data = mcbsp->st_data;

	w = MCBSP_ST_READ(mcbsp, SSELCR);

	MCBSP_ST_WRITE(mcbsp, SGAINCR, ST_CH0GAIN(st_data->ch0gain) |
		       ST_CH1GAIN(st_data->ch1gain));
}