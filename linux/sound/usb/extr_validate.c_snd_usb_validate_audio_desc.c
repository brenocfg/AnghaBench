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

/* Variables and functions */
 int /*<<< orphan*/  audio_validators ; 
 int validate_desc (void*,int,int /*<<< orphan*/ ) ; 

bool snd_usb_validate_audio_desc(void *p, int protocol)
{
	return validate_desc(p, protocol, audio_validators);
}