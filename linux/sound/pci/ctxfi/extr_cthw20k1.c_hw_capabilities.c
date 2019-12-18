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
struct hw {scalar_t__ model; } ;
struct capabilities {int digit_io_switch; scalar_t__ mic_source_switch; scalar_t__ output_switch; scalar_t__ dedicated_mic; } ;

/* Variables and functions */
 scalar_t__ CTSB073X ; 
 scalar_t__ CTUAA ; 

__attribute__((used)) static struct capabilities hw_capabilities(struct hw *hw)
{
	struct capabilities cap;

	/* SB073x and Vista compatible cards have no digit IO switch */
	cap.digit_io_switch = !(hw->model == CTSB073X || hw->model == CTUAA);
	cap.dedicated_mic = 0;
	cap.output_switch = 0;
	cap.mic_source_switch = 0;

	return cap;
}