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
typedef  size_t u32 ;
struct echoaudio {int /*<<< orphan*/ * dsp_registers; } ;

/* Variables and functions */
 size_t readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 get_dsp_register(struct echoaudio *chip, u32 index)
{
	return readl(&chip->dsp_registers[index]);
}