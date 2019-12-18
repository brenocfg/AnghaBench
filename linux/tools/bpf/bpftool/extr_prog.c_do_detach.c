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
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 int EINVAL ; 
 int bpf_prog_detach2 (int,int,int) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*) ; 
 int parse_attach_detach_args (int,char**,int*,int*,int*) ; 

__attribute__((used)) static int do_detach(int argc, char **argv)
{
	enum bpf_attach_type attach_type;
	int err, progfd;
	int mapfd;

	err = parse_attach_detach_args(argc, argv,
				       &progfd, &attach_type, &mapfd);
	if (err)
		return err;

	err = bpf_prog_detach2(progfd, mapfd, attach_type);
	if (err) {
		p_err("failed prog detach from map");
		return -EINVAL;
	}

	if (json_output)
		jsonw_null(json_wtr);
	return 0;
}