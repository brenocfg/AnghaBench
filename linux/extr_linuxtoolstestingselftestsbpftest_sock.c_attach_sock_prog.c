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
 int /*<<< orphan*/  BPF_F_ALLOW_OVERRIDE ; 
 int bpf_prog_attach (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int attach_sock_prog(int cgfd, int progfd,
			    enum bpf_attach_type attach_type)
{
	return bpf_prog_attach(progfd, cgfd, attach_type, BPF_F_ALLOW_OVERRIDE);
}