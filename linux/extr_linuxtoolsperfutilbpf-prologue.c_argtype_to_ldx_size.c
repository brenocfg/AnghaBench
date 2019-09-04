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
 int BPF_B ; 
 int BPF_DW ; 
 int BPF_H ; 
 int BPF_W ; 
 int atoi (char const*) ; 

__attribute__((used)) static int
argtype_to_ldx_size(const char *type)
{
	int arg_size = type ? atoi(&type[1]) : 64;

	switch (arg_size) {
	case 8:
		return BPF_B;
	case 16:
		return BPF_H;
	case 32:
		return BPF_W;
	case 64:
	default:
		return BPF_DW;
	}
}