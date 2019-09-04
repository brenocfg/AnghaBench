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
struct capabilities {int dedicated_mic; int output_switch; int mic_source_switch; scalar_t__ digit_io_switch; } ;

/* Variables and functions */
 scalar_t__ CTSB1270 ; 

__attribute__((used)) static struct capabilities hw_capabilities(struct hw *hw)
{
	struct capabilities cap;

	cap.digit_io_switch = 0;
	cap.dedicated_mic = hw->model == CTSB1270;
	cap.output_switch = hw->model == CTSB1270;
	cap.mic_source_switch = hw->model == CTSB1270;

	return cap;
}