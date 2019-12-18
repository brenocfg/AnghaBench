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
struct ctf_writer {int /*<<< orphan*/  writer; int /*<<< orphan*/  stream_class; int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_ctf_clock_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_ctf_stream_class_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_ctf_writer_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_writer__cleanup_data (struct ctf_writer*) ; 
 int /*<<< orphan*/  free_streams (struct ctf_writer*) ; 
 int /*<<< orphan*/  memset (struct ctf_writer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ctf_writer__cleanup(struct ctf_writer *cw)
{
	ctf_writer__cleanup_data(cw);

	bt_ctf_clock_put(cw->clock);
	free_streams(cw);
	bt_ctf_stream_class_put(cw->stream_class);
	bt_ctf_writer_put(cw->writer);

	/* and NULL all the pointers */
	memset(cw, 0, sizeof(*cw));
}