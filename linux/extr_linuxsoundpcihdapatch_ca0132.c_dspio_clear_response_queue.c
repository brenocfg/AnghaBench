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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int dspio_read (struct hda_codec*,unsigned int*) ; 

__attribute__((used)) static void dspio_clear_response_queue(struct hda_codec *codec)
{
	unsigned int dummy = 0;
	int status = -1;

	/* clear all from the response queue */
	do {
		status = dspio_read(codec, &dummy);
	} while (status == 0);
}