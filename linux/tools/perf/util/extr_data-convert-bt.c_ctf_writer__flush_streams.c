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
struct ctf_writer {int stream_cnt; int /*<<< orphan*/ * stream; } ;

/* Variables and functions */
 int ctf_stream__flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctf_writer__flush_streams(struct ctf_writer *cw)
{
	int cpu, ret = 0;

	for (cpu = 0; cpu < cw->stream_cnt && !ret; cpu++)
		ret = ctf_stream__flush(cw->stream[cpu]);

	return ret;
}