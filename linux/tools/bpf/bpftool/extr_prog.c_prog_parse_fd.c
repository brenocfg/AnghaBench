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

/* Variables and functions */
 int /*<<< orphan*/  BPF_OBJ_PROG ; 
 int /*<<< orphan*/  BPF_TAG_FMT ; 
 int BPF_TAG_SIZE ; 
 int /*<<< orphan*/  NEXT_ARGP () ; 
 int bpf_prog_get_fd_by_id (unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ is_prefix (char*,char*) ; 
 int open_obj_pinned_any (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int prog_fd_by_tag (unsigned char*) ; 
 int sscanf (char*,int /*<<< orphan*/ ,unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 unsigned int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

int prog_parse_fd(int *argc, char ***argv)
{
	int fd;

	if (is_prefix(**argv, "id")) {
		unsigned int id;
		char *endptr;

		NEXT_ARGP();

		id = strtoul(**argv, &endptr, 0);
		if (*endptr) {
			p_err("can't parse %s as ID", **argv);
			return -1;
		}
		NEXT_ARGP();

		fd = bpf_prog_get_fd_by_id(id);
		if (fd < 0)
			p_err("get by id (%u): %s", id, strerror(errno));
		return fd;
	} else if (is_prefix(**argv, "tag")) {
		unsigned char tag[BPF_TAG_SIZE];

		NEXT_ARGP();

		if (sscanf(**argv, BPF_TAG_FMT, tag, tag + 1, tag + 2,
			   tag + 3, tag + 4, tag + 5, tag + 6, tag + 7)
		    != BPF_TAG_SIZE) {
			p_err("can't parse tag");
			return -1;
		}
		NEXT_ARGP();

		return prog_fd_by_tag(tag);
	} else if (is_prefix(**argv, "pinned")) {
		char *path;

		NEXT_ARGP();

		path = **argv;
		NEXT_ARGP();

		return open_obj_pinned_any(path, BPF_OBJ_PROG);
	}

	p_err("expected 'id', 'tag' or 'pinned', got: '%s'?", **argv);
	return -1;
}