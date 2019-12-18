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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ftag ;
typedef  int /*<<< orphan*/  atag ;

/* Variables and functions */
 int BPF_MAXINSNS ; 
 int bpf_try_load_prog (int,int,void (*) (unsigned int,int)) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  tag_exit_report (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tag_from_alg (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tag_from_fdinfo (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void do_test(uint32_t *tests, int start_insns, int fd_map,
		    void (*bpf_filler)(unsigned int insns, int fd))
{
	int i, fd_prog;

	for (i = start_insns; i <= BPF_MAXINSNS; i++) {
		uint8_t ftag[8], atag[sizeof(ftag)];

		fd_prog = bpf_try_load_prog(i, fd_map, bpf_filler);
		tag_from_fdinfo(fd_prog, ftag, sizeof(ftag));
		tag_from_alg(i, atag, sizeof(atag));
		if (memcmp(ftag, atag, sizeof(ftag)))
			tag_exit_report(i, fd_map, ftag, atag, sizeof(ftag));

		close(fd_prog);
		sched_yield();
		(*tests)++;
	}
}