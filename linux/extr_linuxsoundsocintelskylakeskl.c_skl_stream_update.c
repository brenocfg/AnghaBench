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
struct hdac_stream {int /*<<< orphan*/  substream; } ;
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_stream_update(struct hdac_bus *bus, struct hdac_stream *hstr)
{
	snd_pcm_period_elapsed(hstr->substream);
}