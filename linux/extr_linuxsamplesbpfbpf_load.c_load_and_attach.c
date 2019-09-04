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
struct perf_event_attr {int sample_period; int wakeup_events; int config; int /*<<< orphan*/  sample_type; int /*<<< orphan*/  type; } ;
struct bpf_insn {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOG_BUF_SIZE ; 
 int BPF_PROG_TYPE_CGROUP_SKB ; 
 int BPF_PROG_TYPE_CGROUP_SOCK ; 
 int BPF_PROG_TYPE_KPROBE ; 
 int BPF_PROG_TYPE_PERF_EVENT ; 
 int BPF_PROG_TYPE_RAW_TRACEPOINT ; 
 int BPF_PROG_TYPE_SK_MSG ; 
 int BPF_PROG_TYPE_SK_SKB ; 
 int BPF_PROG_TYPE_SOCKET_FILTER ; 
 int BPF_PROG_TYPE_SOCK_OPS ; 
 int BPF_PROG_TYPE_TRACEPOINT ; 
 int BPF_PROG_TYPE_XDP ; 
 int /*<<< orphan*/  DEBUGFS ; 
 int MAX_PROGS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_SET_BPF ; 
 int /*<<< orphan*/  PERF_SAMPLE_RAW ; 
 int /*<<< orphan*/  PERF_TYPE_TRACEPOINT ; 
 int atoi (char*) ; 
 int bpf_load_program (int,struct bpf_insn*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* bpf_log_buf ; 
 int bpf_raw_tracepoint_open (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int* event_fd ; 
 int ioctl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  kern_version ; 
 int /*<<< orphan*/  license ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int populate_prog_array (char const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int prog_cnt ; 
 int* prog_fd ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char,char const*,char const*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char* strerror (int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int sys_perf_event_open (struct perf_event_attr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int write_kprobe_events (char*) ; 

__attribute__((used)) static int load_and_attach(const char *event, struct bpf_insn *prog, int size)
{
	bool is_socket = strncmp(event, "socket", 6) == 0;
	bool is_kprobe = strncmp(event, "kprobe/", 7) == 0;
	bool is_kretprobe = strncmp(event, "kretprobe/", 10) == 0;
	bool is_tracepoint = strncmp(event, "tracepoint/", 11) == 0;
	bool is_raw_tracepoint = strncmp(event, "raw_tracepoint/", 15) == 0;
	bool is_xdp = strncmp(event, "xdp", 3) == 0;
	bool is_perf_event = strncmp(event, "perf_event", 10) == 0;
	bool is_cgroup_skb = strncmp(event, "cgroup/skb", 10) == 0;
	bool is_cgroup_sk = strncmp(event, "cgroup/sock", 11) == 0;
	bool is_sockops = strncmp(event, "sockops", 7) == 0;
	bool is_sk_skb = strncmp(event, "sk_skb", 6) == 0;
	bool is_sk_msg = strncmp(event, "sk_msg", 6) == 0;
	size_t insns_cnt = size / sizeof(struct bpf_insn);
	enum bpf_prog_type prog_type;
	char buf[256];
	int fd, efd, err, id;
	struct perf_event_attr attr = {};

	attr.type = PERF_TYPE_TRACEPOINT;
	attr.sample_type = PERF_SAMPLE_RAW;
	attr.sample_period = 1;
	attr.wakeup_events = 1;

	if (is_socket) {
		prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
	} else if (is_kprobe || is_kretprobe) {
		prog_type = BPF_PROG_TYPE_KPROBE;
	} else if (is_tracepoint) {
		prog_type = BPF_PROG_TYPE_TRACEPOINT;
	} else if (is_raw_tracepoint) {
		prog_type = BPF_PROG_TYPE_RAW_TRACEPOINT;
	} else if (is_xdp) {
		prog_type = BPF_PROG_TYPE_XDP;
	} else if (is_perf_event) {
		prog_type = BPF_PROG_TYPE_PERF_EVENT;
	} else if (is_cgroup_skb) {
		prog_type = BPF_PROG_TYPE_CGROUP_SKB;
	} else if (is_cgroup_sk) {
		prog_type = BPF_PROG_TYPE_CGROUP_SOCK;
	} else if (is_sockops) {
		prog_type = BPF_PROG_TYPE_SOCK_OPS;
	} else if (is_sk_skb) {
		prog_type = BPF_PROG_TYPE_SK_SKB;
	} else if (is_sk_msg) {
		prog_type = BPF_PROG_TYPE_SK_MSG;
	} else {
		printf("Unknown event '%s'\n", event);
		return -1;
	}

	if (prog_cnt == MAX_PROGS)
		return -1;

	fd = bpf_load_program(prog_type, prog, insns_cnt, license, kern_version,
			      bpf_log_buf, BPF_LOG_BUF_SIZE);
	if (fd < 0) {
		printf("bpf_load_program() err=%d\n%s", errno, bpf_log_buf);
		return -1;
	}

	prog_fd[prog_cnt++] = fd;

	if (is_xdp || is_perf_event || is_cgroup_skb || is_cgroup_sk)
		return 0;

	if (is_socket || is_sockops || is_sk_skb || is_sk_msg) {
		if (is_socket)
			event += 6;
		else
			event += 7;
		if (*event != '/')
			return 0;
		event++;
		if (!isdigit(*event)) {
			printf("invalid prog number\n");
			return -1;
		}
		return populate_prog_array(event, fd);
	}

	if (is_raw_tracepoint) {
		efd = bpf_raw_tracepoint_open(event + 15, fd);
		if (efd < 0) {
			printf("tracepoint %s %s\n", event + 15, strerror(errno));
			return -1;
		}
		event_fd[prog_cnt - 1] = efd;
		return 0;
	}

	if (is_kprobe || is_kretprobe) {
		bool need_normal_check = true;
		const char *event_prefix = "";

		if (is_kprobe)
			event += 7;
		else
			event += 10;

		if (*event == 0) {
			printf("event name cannot be empty\n");
			return -1;
		}

		if (isdigit(*event))
			return populate_prog_array(event, fd);

#ifdef __x86_64__
		if (strncmp(event, "sys_", 4) == 0) {
			snprintf(buf, sizeof(buf), "%c:__x64_%s __x64_%s",
				is_kprobe ? 'p' : 'r', event, event);
			err = write_kprobe_events(buf);
			if (err >= 0) {
				need_normal_check = false;
				event_prefix = "__x64_";
			}
		}
#endif
		if (need_normal_check) {
			snprintf(buf, sizeof(buf), "%c:%s %s",
				is_kprobe ? 'p' : 'r', event, event);
			err = write_kprobe_events(buf);
			if (err < 0) {
				printf("failed to create kprobe '%s' error '%s'\n",
				       event, strerror(errno));
				return -1;
			}
		}

		strcpy(buf, DEBUGFS);
		strcat(buf, "events/kprobes/");
		strcat(buf, event_prefix);
		strcat(buf, event);
		strcat(buf, "/id");
	} else if (is_tracepoint) {
		event += 11;

		if (*event == 0) {
			printf("event name cannot be empty\n");
			return -1;
		}
		strcpy(buf, DEBUGFS);
		strcat(buf, "events/");
		strcat(buf, event);
		strcat(buf, "/id");
	}

	efd = open(buf, O_RDONLY, 0);
	if (efd < 0) {
		printf("failed to open event %s\n", event);
		return -1;
	}

	err = read(efd, buf, sizeof(buf));
	if (err < 0 || err >= sizeof(buf)) {
		printf("read from '%s' failed '%s'\n", event, strerror(errno));
		return -1;
	}

	close(efd);

	buf[err] = 0;
	id = atoi(buf);
	attr.config = id;

	efd = sys_perf_event_open(&attr, -1/*pid*/, 0/*cpu*/, -1/*group_fd*/, 0);
	if (efd < 0) {
		printf("event %d fd %d err %s\n", id, efd, strerror(errno));
		return -1;
	}
	event_fd[prog_cnt - 1] = efd;
	err = ioctl(efd, PERF_EVENT_IOC_ENABLE, 0);
	if (err < 0) {
		printf("ioctl PERF_EVENT_IOC_ENABLE failed err %s\n",
		       strerror(errno));
		return -1;
	}
	err = ioctl(efd, PERF_EVENT_IOC_SET_BPF, fd);
	if (err < 0) {
		printf("ioctl PERF_EVENT_IOC_SET_BPF failed err %s\n",
		       strerror(errno));
		return -1;
	}

	return 0;
}