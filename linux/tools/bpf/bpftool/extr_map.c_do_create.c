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
struct bpf_create_map_attr {void* name; scalar_t__ map_ifindex; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; scalar_t__ map_type; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 void* GET_ARG () ; 
 int /*<<< orphan*/  NEXT_ARG () ; 
 int /*<<< orphan*/  REQ_ARGS (int) ; 
 int bpf_create_map_xattr (struct bpf_create_map_attr*) ; 
 int /*<<< orphan*/  close (int) ; 
 int do_pin_fd (int,char const*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ if_nametoindex (char*) ; 
 scalar_t__ is_prefix (char*,char*) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_null (int /*<<< orphan*/ ) ; 
 scalar_t__ map_type_from_str (char*) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 scalar_t__ parse_u32_arg (int*,char***,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_max_rlimit () ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_create(int argc, char **argv)
{
	struct bpf_create_map_attr attr = { NULL, };
	const char *pinfile;
	int err, fd;

	if (!REQ_ARGS(7))
		return -1;
	pinfile = GET_ARG();

	while (argc) {
		if (!REQ_ARGS(2))
			return -1;

		if (is_prefix(*argv, "type")) {
			NEXT_ARG();

			if (attr.map_type) {
				p_err("map type already specified");
				return -1;
			}

			attr.map_type = map_type_from_str(*argv);
			if ((int)attr.map_type < 0) {
				p_err("unrecognized map type: %s", *argv);
				return -1;
			}
			NEXT_ARG();
		} else if (is_prefix(*argv, "name")) {
			NEXT_ARG();
			attr.name = GET_ARG();
		} else if (is_prefix(*argv, "key")) {
			if (parse_u32_arg(&argc, &argv, &attr.key_size,
					  "key size"))
				return -1;
		} else if (is_prefix(*argv, "value")) {
			if (parse_u32_arg(&argc, &argv, &attr.value_size,
					  "value size"))
				return -1;
		} else if (is_prefix(*argv, "entries")) {
			if (parse_u32_arg(&argc, &argv, &attr.max_entries,
					  "max entries"))
				return -1;
		} else if (is_prefix(*argv, "flags")) {
			if (parse_u32_arg(&argc, &argv, &attr.map_flags,
					  "flags"))
				return -1;
		} else if (is_prefix(*argv, "dev")) {
			NEXT_ARG();

			if (attr.map_ifindex) {
				p_err("offload device already specified");
				return -1;
			}

			attr.map_ifindex = if_nametoindex(*argv);
			if (!attr.map_ifindex) {
				p_err("unrecognized netdevice '%s': %s",
				      *argv, strerror(errno));
				return -1;
			}
			NEXT_ARG();
		} else {
			p_err("unknown arg %s", *argv);
			return -1;
		}
	}

	if (!attr.name) {
		p_err("map name not specified");
		return -1;
	}

	set_max_rlimit();

	fd = bpf_create_map_xattr(&attr);
	if (fd < 0) {
		p_err("map create failed: %s", strerror(errno));
		return -1;
	}

	err = do_pin_fd(fd, pinfile);
	close(fd);
	if (err)
		return err;

	if (json_output)
		jsonw_null(json_wtr);
	return 0;
}