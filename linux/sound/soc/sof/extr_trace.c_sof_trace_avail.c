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
struct snd_sof_dev {int /*<<< orphan*/  host_offset; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t sof_trace_avail(struct snd_sof_dev *sdev,
			      loff_t pos, size_t buffer_size)
{
	loff_t host_offset = READ_ONCE(sdev->host_offset);

	/*
	 * If host offset is less than local pos, it means write pointer of
	 * host DMA buffer has been wrapped. We should output the trace data
	 * at the end of host DMA buffer at first.
	 */
	if (host_offset < pos)
		return buffer_size - pos;

	/* If there is available trace data now, it is unnecessary to wait. */
	if (host_offset > pos)
		return host_offset - pos;

	return 0;
}