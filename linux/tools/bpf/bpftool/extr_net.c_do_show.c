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
struct bpf_netdev_t {int used_len; int filter_idx; int /*<<< orphan*/ * devices; scalar_t__ array_len; } ;
struct bpf_attach_info {scalar_t__ flow_dissector_id; } ;
typedef  int /*<<< orphan*/  err_buf ;

/* Variables and functions */
 int /*<<< orphan*/  NET_DUMP_UINT (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  NET_END_ARRAY (char*) ; 
 int /*<<< orphan*/  NET_END_OBJECT ; 
 int /*<<< orphan*/  NET_START_ARRAY (char*,char*) ; 
 int /*<<< orphan*/  NET_START_OBJECT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dump_link_nlmsg ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int libbpf_netlink_open (unsigned int*) ; 
 int libbpf_nl_get_link (int,unsigned int,int /*<<< orphan*/ ,struct bpf_netdev_t*) ; 
 int /*<<< orphan*/  libbpf_strerror (int,char*,int) ; 
 int net_parse_dev (int*,char***) ; 
 int query_flow_dissector (struct bpf_attach_info*) ; 
 int show_dev_tc_bpf (int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int do_show(int argc, char **argv)
{
	struct bpf_attach_info attach_info = {};
	int i, sock, ret, filter_idx = -1;
	struct bpf_netdev_t dev_array;
	unsigned int nl_pid;
	char err_buf[256];

	if (argc == 2) {
		filter_idx = net_parse_dev(&argc, &argv);
		if (filter_idx < 1)
			return -1;
	} else if (argc != 0) {
		usage();
	}

	ret = query_flow_dissector(&attach_info);
	if (ret)
		return -1;

	sock = libbpf_netlink_open(&nl_pid);
	if (sock < 0) {
		fprintf(stderr, "failed to open netlink sock\n");
		return -1;
	}

	dev_array.devices = NULL;
	dev_array.used_len = 0;
	dev_array.array_len = 0;
	dev_array.filter_idx = filter_idx;

	if (json_output)
		jsonw_start_array(json_wtr);
	NET_START_OBJECT;
	NET_START_ARRAY("xdp", "%s:\n");
	ret = libbpf_nl_get_link(sock, nl_pid, dump_link_nlmsg, &dev_array);
	NET_END_ARRAY("\n");

	if (!ret) {
		NET_START_ARRAY("tc", "%s:\n");
		for (i = 0; i < dev_array.used_len; i++) {
			ret = show_dev_tc_bpf(sock, nl_pid,
					      &dev_array.devices[i]);
			if (ret)
				break;
		}
		NET_END_ARRAY("\n");
	}

	NET_START_ARRAY("flow_dissector", "%s:\n");
	if (attach_info.flow_dissector_id > 0)
		NET_DUMP_UINT("id", "id %u", attach_info.flow_dissector_id);
	NET_END_ARRAY("\n");

	NET_END_OBJECT;
	if (json_output)
		jsonw_end_array(json_wtr);

	if (ret) {
		if (json_output)
			jsonw_null(json_wtr);
		libbpf_strerror(ret, err_buf, sizeof(err_buf));
		fprintf(stderr, "Error: %s\n", err_buf);
	}
	free(dev_array.devices);
	close(sock);
	return ret;
}