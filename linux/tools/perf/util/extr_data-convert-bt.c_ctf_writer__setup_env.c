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
struct TYPE_2__ {char* hostname; char* os_release; char* version; char* arch; } ;
struct perf_header {TYPE_1__ env; } ;
struct perf_session {struct perf_header header; } ;
struct ctf_writer {struct bt_ctf_writer* writer; } ;
struct bt_ctf_writer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*) ; 

__attribute__((used)) static int ctf_writer__setup_env(struct ctf_writer *cw,
				 struct perf_session *session)
{
	struct perf_header *header = &session->header;
	struct bt_ctf_writer *writer = cw->writer;

#define ADD(__n, __v)							\
do {									\
	if (bt_ctf_writer_add_environment_field(writer, __n, __v))	\
		return -1;						\
} while (0)

	ADD("host",    header->env.hostname);
	ADD("sysname", "Linux");
	ADD("release", header->env.os_release);
	ADD("version", header->env.version);
	ADD("machine", header->env.arch);
	ADD("domain", "kernel");
	ADD("tracer_name", "perf");

#undef ADD
	return 0;
}