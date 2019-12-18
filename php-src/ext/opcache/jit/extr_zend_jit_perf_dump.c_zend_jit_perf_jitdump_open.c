#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; int process_id; scalar_t__ flags; scalar_t__ time_stamp; int /*<<< orphan*/  elf_mach_target; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ zend_perf_jitdump_header ;
struct TYPE_7__ {int* emagic; int /*<<< orphan*/  machine; } ;
typedef  TYPE_2__ zend_elf_header ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  jit_hdr ;
typedef  int /*<<< orphan*/  elf_hdr ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC ; 
 int KERN_PROC_PATHNAME ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PATH_MAX ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int /*<<< orphan*/  ZEND_PERF_JITDUMP_HEADER_MAGIC ; 
 int /*<<< orphan*/  ZEND_PERF_JITDUMP_HEADER_VERSION ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int getpid () ; 
 int jitdump_fd ; 
 scalar_t__ jitdump_mem ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int,...) ; 
 int read (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_perf_timestamp () ; 
 int /*<<< orphan*/  zend_quiet_write (int,TYPE_1__*,int) ; 

__attribute__((used)) static void zend_jit_perf_jitdump_open(void)
{
	char filename[64];
	int fd, ret;
	zend_elf_header elf_hdr;
	zend_perf_jitdump_header jit_hdr;

	sprintf(filename, "/tmp/jit-%d.dump", getpid());
	if (!zend_perf_timestamp()) {
		return;
	}

#if defined(__linux__)
	fd = open("/proc/self/exe", O_RDONLY);
#elif defined(__NetBSD__)
	fd = open("/proc/curproc/exe", O_RDONLY);
#elif defined(__FreeBSD__)
	char path[PATH_MAX];
	size_t pathlen = sizeof(path);
	int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
	if (sysctl(mib, 4, path, &pathlen, NULL, 0) == -1) {
             return;
	}
	fd = open(path, O_RDONLY);
#else
	fd = -1;
#endif
	if (fd < 0) {
		return;
	}

	ret = read(fd, &elf_hdr, sizeof(elf_hdr));
	close(fd);

	if (ret != sizeof(elf_hdr) ||
	    elf_hdr.emagic[0] != 0x7f ||
	    elf_hdr.emagic[1] != 'E' ||
	    elf_hdr.emagic[2] != 'L' ||
	    elf_hdr.emagic[3] != 'F') {
		return;
	}

	jitdump_fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (jitdump_fd < 0) {
		return;
	}

	jitdump_mem = mmap(NULL,
			sysconf(_SC_PAGESIZE),
			PROT_READ|PROT_EXEC,
			MAP_PRIVATE, jitdump_fd, 0);

	if (jitdump_mem == MAP_FAILED) {
		close(jitdump_fd);
		jitdump_fd = -1;
		return;
	}

	memset(&jit_hdr, 0, sizeof(jit_hdr));
	jit_hdr.magic           = ZEND_PERF_JITDUMP_HEADER_MAGIC;
	jit_hdr.version         = ZEND_PERF_JITDUMP_HEADER_VERSION;
	jit_hdr.size            = sizeof(jit_hdr);
	jit_hdr.elf_mach_target = elf_hdr.machine;
	jit_hdr.process_id      = getpid();
	jit_hdr.time_stamp      = zend_perf_timestamp();
	jit_hdr.flags           = 0;
	zend_quiet_write(jitdump_fd, &jit_hdr, sizeof(jit_hdr));
}