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
struct audio_client {int dummy; } ;

/* Variables and functions */
 int __q6asm_cmd (struct audio_client*,int,int) ; 

int q6asm_cmd_nowait(struct audio_client *ac, int cmd)
{
	return __q6asm_cmd(ac, cmd, false);
}