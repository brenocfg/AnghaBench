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
struct bpf_map_info {int /*<<< orphan*/  type; } ;
typedef  int __u32 ;

/* Variables and functions */
 int BPF_ANY ; 
 int BPF_EXIST ; 
 int BPF_NOEXIST ; 
 int /*<<< orphan*/  fill_per_cpu_value (struct bpf_map_info*,void*) ; 
 scalar_t__ is_prefix (char*,char*) ; 
 scalar_t__ map_is_map_of_maps (int /*<<< orphan*/ ) ; 
 scalar_t__ map_is_map_of_progs (int /*<<< orphan*/ ) ; 
 int map_parse_fd (int*,char***) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int /*<<< orphan*/  p_info (char*) ; 
 char** parse_bytes (char**,char*,void*,int) ; 
 int prog_parse_fd (int*,char***) ; 

__attribute__((used)) static int parse_elem(char **argv, struct bpf_map_info *info,
		      void *key, void *value, __u32 key_size, __u32 value_size,
		      __u32 *flags, __u32 **value_fd)
{
	if (!*argv) {
		if (!key && !value)
			return 0;
		p_err("did not find %s", key ? "key" : "value");
		return -1;
	}

	if (is_prefix(*argv, "key")) {
		if (!key) {
			if (key_size)
				p_err("duplicate key");
			else
				p_err("unnecessary key");
			return -1;
		}

		argv = parse_bytes(argv + 1, "key", key, key_size);
		if (!argv)
			return -1;

		return parse_elem(argv, info, NULL, value, key_size, value_size,
				  flags, value_fd);
	} else if (is_prefix(*argv, "value")) {
		int fd;

		if (!value) {
			if (value_size)
				p_err("duplicate value");
			else
				p_err("unnecessary value");
			return -1;
		}

		argv++;

		if (map_is_map_of_maps(info->type)) {
			int argc = 2;

			if (value_size != 4) {
				p_err("value smaller than 4B for map in map?");
				return -1;
			}
			if (!argv[0] || !argv[1]) {
				p_err("not enough value arguments for map in map");
				return -1;
			}

			fd = map_parse_fd(&argc, &argv);
			if (fd < 0)
				return -1;

			*value_fd = value;
			**value_fd = fd;
		} else if (map_is_map_of_progs(info->type)) {
			int argc = 2;

			if (value_size != 4) {
				p_err("value smaller than 4B for map of progs?");
				return -1;
			}
			if (!argv[0] || !argv[1]) {
				p_err("not enough value arguments for map of progs");
				return -1;
			}
			if (is_prefix(*argv, "id"))
				p_info("Warning: updating program array via MAP_ID, make sure this map is kept open\n"
				       "         by some process or pinned otherwise update will be lost");

			fd = prog_parse_fd(&argc, &argv);
			if (fd < 0)
				return -1;

			*value_fd = value;
			**value_fd = fd;
		} else {
			argv = parse_bytes(argv, "value", value, value_size);
			if (!argv)
				return -1;

			fill_per_cpu_value(info, value);
		}

		return parse_elem(argv, info, key, NULL, key_size, value_size,
				  flags, NULL);
	} else if (is_prefix(*argv, "any") || is_prefix(*argv, "noexist") ||
		   is_prefix(*argv, "exist")) {
		if (!flags) {
			p_err("flags specified multiple times: %s", *argv);
			return -1;
		}

		if (is_prefix(*argv, "any"))
			*flags = BPF_ANY;
		else if (is_prefix(*argv, "noexist"))
			*flags = BPF_NOEXIST;
		else if (is_prefix(*argv, "exist"))
			*flags = BPF_EXIST;

		return parse_elem(argv + 1, info, key, value, key_size,
				  value_size, NULL, value_fd);
	}

	p_err("expected key or value, got: %s", *argv);
	return -1;
}