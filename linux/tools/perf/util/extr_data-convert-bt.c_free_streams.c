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
 int /*<<< orphan*/  ctf_stream__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void free_streams(struct ctf_writer *cw)
{
	int cpu;

	for (cpu = 0; cpu < cw->stream_cnt; cpu++)
		ctf_stream__delete(cw->stream[cpu]);

	zfree(&cw->stream);
}