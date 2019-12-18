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
#define  BPF_B 131 
#define  BPF_DW 130 
#define  BPF_H 129 
#define  BPF_W 128 

__attribute__((used)) static const char *
insn_sz_to_str(int insn_sz)
{
	switch (insn_sz) {
	case BPF_B:
		return "BPF_B";
	case BPF_H:
		return "BPF_H";
	case BPF_W:
		return "BPF_W";
	case BPF_DW:
		return "BPF_DW";
	default:
		return "UNKNOWN";
	}
}