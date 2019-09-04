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
struct sockaddr_in {int dummy; } ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  orig_addr ;
typedef  int /*<<< orphan*/  new_addr ;

/* Variables and functions */
 scalar_t__ PT_REGS_PARM2 (struct pt_regs*) ; 
 scalar_t__ PT_REGS_PARM3 (struct pt_regs*) ; 
 struct sockaddr_in* bpf_map_lookup_elem (int /*<<< orphan*/ *,struct sockaddr_in*) ; 
 scalar_t__ bpf_probe_read (struct sockaddr_in*,int,void*) ; 
 int /*<<< orphan*/  bpf_probe_write_user (void*,struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  dnat_map ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in*,struct sockaddr_in*,int) ; 

int bpf_prog1(struct pt_regs *ctx)
{
	struct sockaddr_in new_addr, orig_addr = {};
	struct sockaddr_in *mapped_addr;
	void *sockaddr_arg = (void *)PT_REGS_PARM2(ctx);
	int sockaddr_len = (int)PT_REGS_PARM3(ctx);

	if (sockaddr_len > sizeof(orig_addr))
		return 0;

	if (bpf_probe_read(&orig_addr, sizeof(orig_addr), sockaddr_arg) != 0)
		return 0;

	mapped_addr = bpf_map_lookup_elem(&dnat_map, &orig_addr);
	if (mapped_addr != NULL) {
		memcpy(&new_addr, mapped_addr, sizeof(new_addr));
		bpf_probe_write_user(sockaddr_arg, &new_addr,
				     sizeof(new_addr));
	}
	return 0;
}