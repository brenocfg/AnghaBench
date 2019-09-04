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
struct thread_data {unsigned int apic_id; unsigned int x2apic_id; int cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIC_X2APIC ; 
 int /*<<< orphan*/  DO_BIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cpuid (int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  genuine_intel ; 
 int /*<<< orphan*/  outf ; 

void get_apic_id(struct thread_data *t)
{
	unsigned int eax, ebx, ecx, edx, max_level;

	eax = ebx = ecx = edx = 0;

	if (!genuine_intel)
		return;

	__cpuid(0, max_level, ebx, ecx, edx);

	__cpuid(1, eax, ebx, ecx, edx);
	t->apic_id = (ebx >> 24) & 0xf;

	if (max_level < 0xb)
		return;

	if (!DO_BIC(BIC_X2APIC))
		return;

	ecx = 0;
	__cpuid(0xb, eax, ebx, ecx, edx);
	t->x2apic_id = edx;

	if (debug && (t->apic_id != t->x2apic_id))
		fprintf(outf, "cpu%d: apic 0x%x x2apic 0x%x\n", t->cpu_id, t->apic_id, t->x2apic_id);
}