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
struct ctf_stream {scalar_t__ count; int /*<<< orphan*/  cpu; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int bt_ctf_stream_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctf_stream__flush(struct ctf_stream *cs)
{
	int err = 0;

	if (cs) {
		err = bt_ctf_stream_flush(cs->stream);
		if (err)
			pr_err("CTF stream %d flush failed\n", cs->cpu);

		pr("Flush stream for cpu %d (%u samples)\n",
		   cs->cpu, cs->count);

		cs->count = 0;
	}

	return err;
}