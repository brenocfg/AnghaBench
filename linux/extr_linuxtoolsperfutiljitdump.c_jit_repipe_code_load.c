#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned long size; } ;
struct TYPE_14__ {TYPE_4__ header; } ;
struct TYPE_11__ {int size; void* misc; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {char* filename; int len; int pid; int tid; int ino_generation; int /*<<< orphan*/  flags; int /*<<< orphan*/  prot; int /*<<< orphan*/  min; int /*<<< orphan*/  maj; int /*<<< orphan*/  ino; void* start; int /*<<< orphan*/  pgoff; TYPE_2__ header; } ;
union perf_event {TYPE_5__ mmap; TYPE_3__ mmap2; } ;
struct TYPE_16__ {int /*<<< orphan*/  timestamp; void* total_size; } ;
struct TYPE_15__ {int pid; int tid; int code_size; int code_index; TYPE_7__ p; void* code_addr; } ;
union jr_entry {TYPE_6__ load; } ;
typedef  void* uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct stat {int pid; int tid; void* ip; int /*<<< orphan*/  time; void* cpumode; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_ino; } ;
struct perf_tool {int dummy; } ;
struct perf_sample {int pid; int tid; void* ip; int /*<<< orphan*/  time; void* cpumode; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_ino; } ;
struct jit_buf_desc {int unwinding_mapped_size; char* dir; int sample_type; TYPE_8__* machine; int /*<<< orphan*/  unwinding_size; int /*<<< orphan*/  eh_frame_hdr_size; union perf_event* unwinding_data; int /*<<< orphan*/  nr_debug_entries; union perf_event* debug_data; TYPE_1__* session; } ;
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  sample ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_17__ {int id_hdr_size; } ;
struct TYPE_10__ {struct perf_tool* tool; } ;

/* Variables and functions */
 int ALIGN_8 (int) ; 
 int /*<<< orphan*/  GEN_ELF_TEXT_OFFSET ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PATH_MAX ; 
 size_t PERF_ALIGN (size_t,int) ; 
 void* PERF_RECORD_MISC_USER ; 
 int /*<<< orphan*/  PERF_RECORD_MMAP2 ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 int /*<<< orphan*/  build_id__mark_dso_hit (struct perf_tool*,union perf_event*,struct stat*,int /*<<< orphan*/ *,TYPE_8__*) ; 
 union perf_event* calloc (int,int) ; 
 int /*<<< orphan*/  convert_timestamp (struct jit_buf_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (union perf_event*) ; 
 int jit_emit_elf (char*,char const*,void*,void const*,int,union perf_event*,int /*<<< orphan*/ ,union perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jit_inject_event (struct jit_buf_desc*,union perf_event*) ; 
 int /*<<< orphan*/  major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 int perf_event__process_mmap2 (struct perf_tool*,union perf_event*,struct stat*,TYPE_8__*) ; 
 size_t snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int jit_repipe_code_load(struct jit_buf_desc *jd, union jr_entry *jr)
{
	struct perf_sample sample;
	union perf_event *event;
	struct perf_tool *tool = jd->session->tool;
	uint64_t code, addr;
	uintptr_t uaddr;
	char *filename;
	struct stat st;
	size_t size;
	u16 idr_size;
	const char *sym;
	uint32_t count;
	int ret, csize, usize;
	pid_t pid, tid;
	struct {
		u32 pid, tid;
		u64 time;
	} *id;

	pid   = jr->load.pid;
	tid   = jr->load.tid;
	csize = jr->load.code_size;
	usize = jd->unwinding_mapped_size;
	addr  = jr->load.code_addr;
	sym   = (void *)((unsigned long)jr + sizeof(jr->load));
	code  = (unsigned long)jr + jr->load.p.total_size - csize;
	count = jr->load.code_index;
	idr_size = jd->machine->id_hdr_size;

	event = calloc(1, sizeof(*event) + idr_size);
	if (!event)
		return -1;

	filename = event->mmap2.filename;
	size = snprintf(filename, PATH_MAX, "%s/jitted-%d-%u.so",
			jd->dir,
			pid,
			count);

	size++; /* for \0 */

	size = PERF_ALIGN(size, sizeof(u64));
	uaddr = (uintptr_t)code;
	ret = jit_emit_elf(filename, sym, addr, (const void *)uaddr, csize, jd->debug_data, jd->nr_debug_entries,
			   jd->unwinding_data, jd->eh_frame_hdr_size, jd->unwinding_size);

	if (jd->debug_data && jd->nr_debug_entries) {
		free(jd->debug_data);
		jd->debug_data = NULL;
		jd->nr_debug_entries = 0;
	}

	if (jd->unwinding_data && jd->eh_frame_hdr_size) {
		free(jd->unwinding_data);
		jd->unwinding_data = NULL;
		jd->eh_frame_hdr_size = 0;
		jd->unwinding_mapped_size = 0;
		jd->unwinding_size = 0;
	}

	if (ret) {
		free(event);
		return -1;
	}
	if (stat(filename, &st))
		memset(&st, 0, sizeof(st));

	event->mmap2.header.type = PERF_RECORD_MMAP2;
	event->mmap2.header.misc = PERF_RECORD_MISC_USER;
	event->mmap2.header.size = (sizeof(event->mmap2) -
			(sizeof(event->mmap2.filename) - size) + idr_size);

	event->mmap2.pgoff = GEN_ELF_TEXT_OFFSET;
	event->mmap2.start = addr;
	event->mmap2.len   = usize ? ALIGN_8(csize) + usize : csize;
	event->mmap2.pid   = pid;
	event->mmap2.tid   = tid;
	event->mmap2.ino   = st.st_ino;
	event->mmap2.maj   = major(st.st_dev);
	event->mmap2.min   = minor(st.st_dev);
	event->mmap2.prot  = st.st_mode;
	event->mmap2.flags = MAP_SHARED;
	event->mmap2.ino_generation = 1;

	id = (void *)((unsigned long)event + event->mmap.header.size - idr_size);
	if (jd->sample_type & PERF_SAMPLE_TID) {
		id->pid  = pid;
		id->tid  = tid;
	}
	if (jd->sample_type & PERF_SAMPLE_TIME)
		id->time = convert_timestamp(jd, jr->load.p.timestamp);

	/*
	 * create pseudo sample to induce dso hit increment
	 * use first address as sample address
	 */
	memset(&sample, 0, sizeof(sample));
	sample.cpumode = PERF_RECORD_MISC_USER;
	sample.pid  = pid;
	sample.tid  = tid;
	sample.time = id->time;
	sample.ip   = addr;

	ret = perf_event__process_mmap2(tool, event, &sample, jd->machine);
	if (ret)
		return ret;

	ret = jit_inject_event(jd, event);
	/*
	 * mark dso as use to generate buildid in the header
	 */
	if (!ret)
		build_id__mark_dso_hit(tool, event, &sample, NULL, jd->machine);

	return ret;
}