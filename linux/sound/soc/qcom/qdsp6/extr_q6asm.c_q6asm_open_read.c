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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct audio_client {int dummy; } ;

/* Variables and functions */
 int __q6asm_open_read (struct audio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int q6asm_open_read(struct audio_client *ac, uint32_t format,
			uint16_t bits_per_sample)
{
	return __q6asm_open_read(ac, format, bits_per_sample);
}