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
struct ctf_writer {struct ctf_stream** stream; } ;
struct ctf_stream {int dummy; } ;

/* Variables and functions */
 struct ctf_stream* ctf_stream__create (struct ctf_writer*,int) ; 

__attribute__((used)) static struct ctf_stream *ctf_stream(struct ctf_writer *cw, int cpu)
{
	struct ctf_stream *cs = cw->stream[cpu];

	if (!cs) {
		cs = ctf_stream__create(cw, cpu);
		cw->stream[cpu] = cs;
	}

	return cs;
}