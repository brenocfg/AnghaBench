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
typedef  int /*<<< orphan*/  u32 ;
struct hdac_ext_stream {int /*<<< orphan*/  hstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_LPIB ; 
 int /*<<< orphan*/  snd_hdac_stream_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_hdac_ext_stream_set_lpib(struct hdac_ext_stream *stream, u32 value)
{
	snd_hdac_stream_writel(&stream->hstream, SD_LPIB, value);

	return 0;
}