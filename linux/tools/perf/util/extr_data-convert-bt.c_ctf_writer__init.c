#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  u32; } ;
struct ctf_writer {TYPE_1__ data; struct bt_ctf_stream_class* stream_class; struct bt_ctf_clock* clock; struct bt_ctf_writer* writer; } ;
struct bt_ctf_writer {int dummy; } ;
struct bt_ctf_stream_class {int dummy; } ;
struct bt_ctf_field_type {int dummy; } ;
struct bt_ctf_clock {int dummy; } ;

/* Variables and functions */
 struct bt_ctf_clock* bt_ctf_clock_create (char*) ; 
 int /*<<< orphan*/  bt_ctf_field_type_put (struct bt_ctf_field_type*) ; 
 int bt_ctf_field_type_structure_add_field (struct bt_ctf_field_type*,int /*<<< orphan*/ ,char*) ; 
 struct bt_ctf_stream_class* bt_ctf_stream_class_create (char*) ; 
 struct bt_ctf_field_type* bt_ctf_stream_class_get_packet_context_type (struct bt_ctf_stream_class*) ; 
 scalar_t__ bt_ctf_stream_class_set_clock (struct bt_ctf_stream_class*,struct bt_ctf_clock*) ; 
 scalar_t__ bt_ctf_writer_add_clock (struct bt_ctf_writer*,struct bt_ctf_clock*) ; 
 struct bt_ctf_writer* bt_ctf_writer_create (char const*) ; 
 int /*<<< orphan*/  ctf_writer__cleanup (struct ctf_writer*) ; 
 scalar_t__ ctf_writer__init_data (struct ctf_writer*) ; 
 scalar_t__ ctf_writer__setup_clock (struct ctf_writer*) ; 
 int /*<<< orphan*/  pr (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ctf_writer__init(struct ctf_writer *cw, const char *path)
{
	struct bt_ctf_writer		*writer;
	struct bt_ctf_stream_class	*stream_class;
	struct bt_ctf_clock		*clock;
	struct bt_ctf_field_type	*pkt_ctx_type;
	int				ret;

	/* CTF writer */
	writer = bt_ctf_writer_create(path);
	if (!writer)
		goto err;

	cw->writer = writer;

	/* CTF clock */
	clock = bt_ctf_clock_create("perf_clock");
	if (!clock) {
		pr("Failed to create CTF clock.\n");
		goto err_cleanup;
	}

	cw->clock = clock;

	if (ctf_writer__setup_clock(cw)) {
		pr("Failed to setup CTF clock.\n");
		goto err_cleanup;
	}

	/* CTF stream class */
	stream_class = bt_ctf_stream_class_create("perf_stream");
	if (!stream_class) {
		pr("Failed to create CTF stream class.\n");
		goto err_cleanup;
	}

	cw->stream_class = stream_class;

	/* CTF clock stream setup */
	if (bt_ctf_stream_class_set_clock(stream_class, clock)) {
		pr("Failed to assign CTF clock to stream class.\n");
		goto err_cleanup;
	}

	if (ctf_writer__init_data(cw))
		goto err_cleanup;

	/* Add cpu_id for packet context */
	pkt_ctx_type = bt_ctf_stream_class_get_packet_context_type(stream_class);
	if (!pkt_ctx_type)
		goto err_cleanup;

	ret = bt_ctf_field_type_structure_add_field(pkt_ctx_type, cw->data.u32, "cpu_id");
	bt_ctf_field_type_put(pkt_ctx_type);
	if (ret)
		goto err_cleanup;

	/* CTF clock writer setup */
	if (bt_ctf_writer_add_clock(writer, clock)) {
		pr("Failed to assign CTF clock to writer.\n");
		goto err_cleanup;
	}

	return 0;

err_cleanup:
	ctf_writer__cleanup(cw);
err:
	pr_err("Failed to setup CTF writer.\n");
	return -1;
}