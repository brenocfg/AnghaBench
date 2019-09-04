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
struct ctf_writer {int /*<<< orphan*/  stream_class; int /*<<< orphan*/  writer; } ;
struct ctf_stream {int cpu; struct bt_ctf_stream* stream; } ;
struct bt_ctf_stream {int dummy; } ;
struct bt_ctf_field {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_ctf_field_put (struct bt_ctf_field*) ; 
 struct bt_ctf_field* bt_ctf_field_structure_get_field (struct bt_ctf_field*,char*) ; 
 int bt_ctf_field_unsigned_integer_set_value (struct bt_ctf_field*,int /*<<< orphan*/ ) ; 
 struct bt_ctf_field* bt_ctf_stream_get_packet_context (struct bt_ctf_stream*) ; 
 int /*<<< orphan*/  bt_ctf_stream_put (struct bt_ctf_stream*) ; 
 struct bt_ctf_stream* bt_ctf_writer_create_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ctf_stream*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct ctf_stream* zalloc (int) ; 

__attribute__((used)) static struct ctf_stream *ctf_stream__create(struct ctf_writer *cw, int cpu)
{
	struct ctf_stream *cs;
	struct bt_ctf_field *pkt_ctx   = NULL;
	struct bt_ctf_field *cpu_field = NULL;
	struct bt_ctf_stream *stream   = NULL;
	int ret;

	cs = zalloc(sizeof(*cs));
	if (!cs) {
		pr_err("Failed to allocate ctf stream\n");
		return NULL;
	}

	stream = bt_ctf_writer_create_stream(cw->writer, cw->stream_class);
	if (!stream) {
		pr_err("Failed to create CTF stream\n");
		goto out;
	}

	pkt_ctx = bt_ctf_stream_get_packet_context(stream);
	if (!pkt_ctx) {
		pr_err("Failed to obtain packet context\n");
		goto out;
	}

	cpu_field = bt_ctf_field_structure_get_field(pkt_ctx, "cpu_id");
	bt_ctf_field_put(pkt_ctx);
	if (!cpu_field) {
		pr_err("Failed to obtain cpu field\n");
		goto out;
	}

	ret = bt_ctf_field_unsigned_integer_set_value(cpu_field, (u32) cpu);
	if (ret) {
		pr_err("Failed to update CPU number\n");
		goto out;
	}

	bt_ctf_field_put(cpu_field);

	cs->cpu    = cpu;
	cs->stream = stream;
	return cs;

out:
	if (cpu_field)
		bt_ctf_field_put(cpu_field);
	if (stream)
		bt_ctf_stream_put(stream);

	free(cs);
	return NULL;
}