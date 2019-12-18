#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bpf_prog_test_run_attr {int prog_fd; int data_size_in; int ctx_size_in; int data_size_out; int retval; int /*<<< orphan*/  duration; struct bpf_flow_keys* ctx_in; struct bpf_flow_keys* data_out; int /*<<< orphan*/ * data_in; } ;
struct bpf_object {int dummy; } ;
struct bpf_flow_keys {int flags; } ;
typedef  int /*<<< orphan*/  flow_keys ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int __u32 ;
struct TYPE_5__ {int dport; scalar_t__ sport; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  name; TYPE_2__ keys; int /*<<< orphan*/  pkt; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BPF_FLOW_DISSECTOR ; 
 int BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_ATTR (int,int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ CHECK_FAIL (int) ; 
 int /*<<< orphan*/  CHECK_FLOW_KEYS (int /*<<< orphan*/ ,struct bpf_flow_keys,TYPE_2__) ; 
 int bpf_flow_load (struct bpf_object**,char*,char*,char*,char*,int*,int*) ; 
 int bpf_map_delete_elem (int,int*) ; 
 int bpf_map_lookup_elem (int,int*,struct bpf_flow_keys*) ; 
 int /*<<< orphan*/  bpf_object__close (struct bpf_object*) ; 
 int bpf_prog_attach (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_detach (int,int /*<<< orphan*/ ) ; 
 int bpf_prog_test_run_xattr (struct bpf_prog_test_run_attr*) ; 
 int create_tap (char*) ; 
 int /*<<< orphan*/  errno ; 
 int ifup (char*) ; 
 TYPE_1__* tests ; 
 int tx_tap (int,int /*<<< orphan*/ *,int) ; 

void test_flow_dissector(void)
{
	int i, err, prog_fd, keys_fd = -1, tap_fd;
	struct bpf_object *obj;
	__u32 duration = 0;

	err = bpf_flow_load(&obj, "./bpf_flow.o", "flow_dissector",
			    "jmp_table", "last_dissection", &prog_fd, &keys_fd);
	if (CHECK_FAIL(err))
		return;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct bpf_flow_keys flow_keys;
		struct bpf_prog_test_run_attr tattr = {
			.prog_fd = prog_fd,
			.data_in = &tests[i].pkt,
			.data_size_in = sizeof(tests[i].pkt),
			.data_out = &flow_keys,
		};
		static struct bpf_flow_keys ctx = {};

		if (tests[i].flags) {
			tattr.ctx_in = &ctx;
			tattr.ctx_size_in = sizeof(ctx);
			ctx.flags = tests[i].flags;
		}

		err = bpf_prog_test_run_xattr(&tattr);
		CHECK_ATTR(tattr.data_size_out != sizeof(flow_keys) ||
			   err || tattr.retval != 1,
			   tests[i].name,
			   "err %d errno %d retval %d duration %d size %u/%lu\n",
			   err, errno, tattr.retval, tattr.duration,
			   tattr.data_size_out, sizeof(flow_keys));
		CHECK_FLOW_KEYS(tests[i].name, flow_keys, tests[i].keys);
	}

	/* Do the same tests but for skb-less flow dissector.
	 * We use a known path in the net/tun driver that calls
	 * eth_get_headlen and we manually export bpf_flow_keys
	 * via BPF map in this case.
	 */

	err = bpf_prog_attach(prog_fd, 0, BPF_FLOW_DISSECTOR, 0);
	CHECK(err, "bpf_prog_attach", "err %d errno %d\n", err, errno);

	tap_fd = create_tap("tap0");
	CHECK(tap_fd < 0, "create_tap", "tap_fd %d errno %d\n", tap_fd, errno);
	err = ifup("tap0");
	CHECK(err, "ifup", "err %d errno %d\n", err, errno);

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		/* Keep in sync with 'flags' from eth_get_headlen. */
		__u32 eth_get_headlen_flags =
			BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG;
		struct bpf_prog_test_run_attr tattr = {};
		struct bpf_flow_keys flow_keys = {};
		__u32 key = (__u32)(tests[i].keys.sport) << 16 |
			    tests[i].keys.dport;

		/* For skb-less case we can't pass input flags; run
		 * only the tests that have a matching set of flags.
		 */

		if (tests[i].flags != eth_get_headlen_flags)
			continue;

		err = tx_tap(tap_fd, &tests[i].pkt, sizeof(tests[i].pkt));
		CHECK(err < 0, "tx_tap", "err %d errno %d\n", err, errno);

		err = bpf_map_lookup_elem(keys_fd, &key, &flow_keys);
		CHECK_ATTR(err, tests[i].name, "bpf_map_lookup_elem %d\n", err);

		CHECK_ATTR(err, tests[i].name, "skb-less err %d\n", err);
		CHECK_FLOW_KEYS(tests[i].name, flow_keys, tests[i].keys);

		err = bpf_map_delete_elem(keys_fd, &key);
		CHECK_ATTR(err, tests[i].name, "bpf_map_delete_elem %d\n", err);
	}

	bpf_prog_detach(prog_fd, BPF_FLOW_DISSECTOR);
	bpf_object__close(obj);
}