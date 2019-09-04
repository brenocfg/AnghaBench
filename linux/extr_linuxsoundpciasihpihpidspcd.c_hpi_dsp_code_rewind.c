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
struct dsp_code {int word_count; } ;
struct code_header {int dummy; } ;

/* Variables and functions */

void hpi_dsp_code_rewind(struct dsp_code *dsp_code)
{
	/* Go back to start of  data, after header */
	dsp_code->word_count = sizeof(struct code_header) / sizeof(u32);
}