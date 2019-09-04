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
struct jitheader {int total_size; int pid; int /*<<< orphan*/  flags; scalar_t__ timestamp; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  header ;
typedef  void FILE ;

/* Variables and functions */
 int /*<<< orphan*/  JITDUMP_FLAGS_ARCH_TIMESTAMP ; 
 int /*<<< orphan*/  JITHEADER_MAGIC ; 
 int /*<<< orphan*/  JITHEADER_VERSION ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ create_jit_cache_dir () ; 
 int /*<<< orphan*/  fclose (void*) ; 
 void* fdopen (int,char*) ; 
 int /*<<< orphan*/  fwrite (struct jitheader*,int,int,void*) ; 
 scalar_t__ get_e_machine (struct jitheader*) ; 
 int getpid () ; 
 int /*<<< orphan*/  init_arch_timestamp () ; 
 char* jit_path ; 
 int /*<<< orphan*/  memset (struct jitheader*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int,int) ; 
 char* perf_clk_id ; 
 scalar_t__ perf_get_timestamp () ; 
 scalar_t__ perf_open_marker_file (int) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 scalar_t__ use_arch_timestamp ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void *jvmti_open(void)
{
	char dump_path[PATH_MAX];
	struct jitheader header;
	int fd, ret;
	FILE *fp;

	init_arch_timestamp();

	/*
	 * check if clockid is supported
	 */
	if (!perf_get_timestamp()) {
		if (use_arch_timestamp)
			warnx("jvmti: arch timestamp not supported");
		else
			warnx("jvmti: kernel does not support %d clock id", perf_clk_id);
	}

	memset(&header, 0, sizeof(header));

	/*
	 * jitdump file dir
	 */
	if (create_jit_cache_dir() < 0)
		return NULL;

	/*
	 * jitdump file name
	 */
	ret = snprintf(dump_path, PATH_MAX, "%s/jit-%i.dump", jit_path, getpid());
	if (ret >= PATH_MAX) {
		warnx("jvmti: cannot generate jitdump file full path because"
			" %s/jit-%i.dump is too long, please check the cwd,"
			" JITDUMPDIR, and HOME variables", jit_path, getpid());
		return NULL;
	}

	fd = open(dump_path, O_CREAT|O_TRUNC|O_RDWR, 0666);
	if (fd == -1)
		return NULL;

	/*
	 * create perf.data maker for the jitdump file
	 */
	if (perf_open_marker_file(fd)) {
		warnx("jvmti: failed to create marker file");
		return NULL;
	}

	fp = fdopen(fd, "w+");
	if (!fp) {
		warn("jvmti: cannot create %s", dump_path);
		close(fd);
		goto error;
	}

	warnx("jvmti: jitdump in %s", dump_path);

	if (get_e_machine(&header)) {
		warn("get_e_machine failed\n");
		goto error;
	}

	header.magic      = JITHEADER_MAGIC;
	header.version    = JITHEADER_VERSION;
	header.total_size = sizeof(header);
	header.pid        = getpid();

	header.timestamp = perf_get_timestamp();

	if (use_arch_timestamp)
		header.flags |= JITDUMP_FLAGS_ARCH_TIMESTAMP;

	if (!fwrite(&header, sizeof(header), 1, fp)) {
		warn("jvmti: cannot write dumpfile header");
		goto error;
	}
	return fp;
error:
	fclose(fp);
	return NULL;
}