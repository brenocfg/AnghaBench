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
struct hw20k2 {int mic_source; } ;
struct hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int hw_mic_source_switch_get(struct hw *hw)
{
	struct hw20k2 *hw20k2 = (struct hw20k2 *)hw;

	return hw20k2->mic_source;
}