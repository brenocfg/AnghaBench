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
struct audio_repack {scalar_t__ packet_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct audio_repack*,int /*<<< orphan*/ ,int) ; 

void audio_repack_free(struct audio_repack *repack)
{
	if (repack->packet_buffer)
		bfree(repack->packet_buffer);

	memset(repack, 0, sizeof(*repack));
}