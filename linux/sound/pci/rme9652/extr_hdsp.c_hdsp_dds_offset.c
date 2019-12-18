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
typedef  int u64 ;
struct hdsp {unsigned int dds_value; int system_sample_rate; } ;

/* Variables and functions */
 int DDS_NUMERATOR ; 
 int div_u64 (int,unsigned int) ; 

__attribute__((used)) static int hdsp_dds_offset(struct hdsp *hdsp)
{
	u64 n;
	unsigned int dds_value = hdsp->dds_value;
	int system_sample_rate = hdsp->system_sample_rate;

	if (!dds_value)
		return 0;

	n = DDS_NUMERATOR;
	/*
	 * dds_value = n / rate
	 * rate = n / dds_value
	 */
	n = div_u64(n, dds_value);
	if (system_sample_rate >= 112000)
		n *= 4;
	else if (system_sample_rate >= 56000)
		n *= 2;
	return ((int)n) - system_sample_rate;
}