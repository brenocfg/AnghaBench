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
struct dsp_code {TYPE_1__* pvt; } ;
struct TYPE_2__ {int /*<<< orphan*/  firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

void hpi_dsp_code_close(struct dsp_code *dsp_code)
{
	HPI_DEBUG_LOG(DEBUG, "dsp code closed\n");
	release_firmware(dsp_code->pvt->firmware);
	kfree(dsp_code->pvt);
}