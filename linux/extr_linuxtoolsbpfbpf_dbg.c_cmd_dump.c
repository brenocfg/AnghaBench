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
 int CMD_ERR ; 
 int CMD_OK ; 
 int /*<<< orphan*/  bpf_dump_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_image ; 
 int /*<<< orphan*/  bpf_prog_len ; 
 int /*<<< orphan*/  bpf_prog_loaded () ; 

__attribute__((used)) static int cmd_dump(char *dontcare)
{
	if (!bpf_prog_loaded())
		return CMD_ERR;

	bpf_dump_all(bpf_image, bpf_prog_len);

	return CMD_OK;
}