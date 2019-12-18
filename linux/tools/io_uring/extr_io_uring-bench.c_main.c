#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* ring_entries; } ;
struct TYPE_5__ {int* ring_entries; } ;
struct submitter {int nr_files; int /*<<< orphan*/  ring_fd; int /*<<< orphan*/  thread; int /*<<< orphan*/  inflight; scalar_t__ reaps; scalar_t__ calls; scalar_t__ done; TYPE_3__ cq_ring; TYPE_2__ sq_ring; TYPE_1__* iovecs; struct file* files; } ;
struct rlimit {void* rlim_max; void* rlim_cur; } ;
struct file {int real_fd; int max_blocks; } ;
struct TYPE_4__ {int /*<<< orphan*/  iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS ; 
 int DEPTH ; 
 int MAX_FDS ; 
 int O_DIRECT ; 
 int O_NOATIME ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 void* RLIM_INFINITY ; 
 int /*<<< orphan*/  arm_sig_int () ; 
 int buffered ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_nop ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  file_depths (char*) ; 
 int /*<<< orphan*/  finish ; 
 int fixedbufs ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_file_size (struct file*) ; 
 char* malloc (int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int polled ; 
 scalar_t__ posix_memalign (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct submitter*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int setup_ring (struct submitter*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submitter_fn ; 
 struct submitter* submitters ; 

int main(int argc, char *argv[])
{
	struct submitter *s = &submitters[0];
	unsigned long done, calls, reap;
	int err, i, flags, fd;
	char *fdepths;
	void *ret;

	if (!do_nop && argc < 2) {
		printf("%s: filename\n", argv[0]);
		return 1;
	}

	flags = O_RDONLY | O_NOATIME;
	if (!buffered)
		flags |= O_DIRECT;

	i = 1;
	while (!do_nop && i < argc) {
		struct file *f;

		if (s->nr_files == MAX_FDS) {
			printf("Max number of files (%d) reached\n", MAX_FDS);
			break;
		}
		fd = open(argv[i], flags);
		if (fd < 0) {
			perror("open");
			return 1;
		}

		f = &s->files[s->nr_files];
		f->real_fd = fd;
		if (get_file_size(f)) {
			printf("failed getting size of device/file\n");
			return 1;
		}
		if (f->max_blocks <= 1) {
			printf("Zero file/device size?\n");
			return 1;
		}
		f->max_blocks--;

		printf("Added file %s\n", argv[i]);
		s->nr_files++;
		i++;
	}

	if (fixedbufs) {
		struct rlimit rlim;

		rlim.rlim_cur = RLIM_INFINITY;
		rlim.rlim_max = RLIM_INFINITY;
		if (setrlimit(RLIMIT_MEMLOCK, &rlim) < 0) {
			perror("setrlimit");
			return 1;
		}
	}

	arm_sig_int();

	for (i = 0; i < DEPTH; i++) {
		void *buf;

		if (posix_memalign(&buf, BS, BS)) {
			printf("failed alloc\n");
			return 1;
		}
		s->iovecs[i].iov_base = buf;
		s->iovecs[i].iov_len = BS;
	}

	err = setup_ring(s);
	if (err) {
		printf("ring setup failed: %s, %d\n", strerror(errno), err);
		return 1;
	}
	printf("polled=%d, fixedbufs=%d, buffered=%d", polled, fixedbufs, buffered);
	printf(" QD=%d, sq_ring=%d, cq_ring=%d\n", DEPTH, *s->sq_ring.ring_entries, *s->cq_ring.ring_entries);

	pthread_create(&s->thread, NULL, submitter_fn, s);

	fdepths = malloc(8 * s->nr_files);
	reap = calls = done = 0;
	do {
		unsigned long this_done = 0;
		unsigned long this_reap = 0;
		unsigned long this_call = 0;
		unsigned long rpc = 0, ipc = 0;

		sleep(1);
		this_done += s->done;
		this_call += s->calls;
		this_reap += s->reaps;
		if (this_call - calls) {
			rpc = (this_done - done) / (this_call - calls);
			ipc = (this_reap - reap) / (this_call - calls);
		} else
			rpc = ipc = -1;
		file_depths(fdepths);
		printf("IOPS=%lu, IOS/call=%ld/%ld, inflight=%u (%s)\n",
				this_done - done, rpc, ipc, s->inflight,
				fdepths);
		done = this_done;
		calls = this_call;
		reap = this_reap;
	} while (!finish);

	pthread_join(s->thread, &ret);
	close(s->ring_fd);
	free(fdepths);
	return 0;
}