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
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_ADSP_ERROR_CODE ; 
 unsigned int sst_dsp_shim_read (struct sst_dsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int cnl_get_errno(struct sst_dsp *ctx)
{
	return sst_dsp_shim_read(ctx, CNL_ADSP_ERROR_CODE);
}