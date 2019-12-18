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
struct bpf_program {int dummy; } ;
struct bpf_link {int dummy; } ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 struct bpf_link* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct bpf_link*) ; 
 int PTR_ERR (struct bpf_link*) ; 
 int STRERR_BUFSIZE ; 
 struct bpf_link* bpf_program__attach_perf_event (struct bpf_program*,int) ; 
 int /*<<< orphan*/  bpf_program__title (struct bpf_program*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  libbpf_strerror_r (int,char*,int) ; 
 int perf_event_open_tracepoint (char const*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 

struct bpf_link *bpf_program__attach_tracepoint(struct bpf_program *prog,
						const char *tp_category,
						const char *tp_name)
{
	char errmsg[STRERR_BUFSIZE];
	struct bpf_link *link;
	int pfd, err;

	pfd = perf_event_open_tracepoint(tp_category, tp_name);
	if (pfd < 0) {
		pr_warning("program '%s': failed to create tracepoint '%s/%s' perf event: %s\n",
			   bpf_program__title(prog, false),
			   tp_category, tp_name,
			   libbpf_strerror_r(pfd, errmsg, sizeof(errmsg)));
		return ERR_PTR(pfd);
	}
	link = bpf_program__attach_perf_event(prog, pfd);
	if (IS_ERR(link)) {
		close(pfd);
		err = PTR_ERR(link);
		pr_warning("program '%s': failed to attach to tracepoint '%s/%s': %s\n",
			   bpf_program__title(prog, false),
			   tp_category, tp_name,
			   libbpf_strerror_r(err, errmsg, sizeof(errmsg)));
		return link;
	}
	return link;
}