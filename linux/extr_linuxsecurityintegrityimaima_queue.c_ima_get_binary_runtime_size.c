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
struct ima_kexec_hdr {int dummy; } ;

/* Variables and functions */
 int ULONG_MAX ; 
 int binary_runtime_size ; 

unsigned long ima_get_binary_runtime_size(void)
{
	if (binary_runtime_size >= (ULONG_MAX - sizeof(struct ima_kexec_hdr)))
		return ULONG_MAX;
	else
		return binary_runtime_size + sizeof(struct ima_kexec_hdr);
}