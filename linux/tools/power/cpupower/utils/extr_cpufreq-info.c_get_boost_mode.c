#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_frequencies {int /*<<< orphan*/  frequency; struct cpufreq_frequencies* next; } ;
struct TYPE_2__ {scalar_t__ vendor; } ;

/* Variables and functions */
 scalar_t__ X86_VENDOR_AMD ; 
 scalar_t__ X86_VENDOR_HYGON ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 char* _ (char*) ; 
 struct cpufreq_frequencies* cpufreq_get_frequencies (char*,unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_frequencies (struct cpufreq_frequencies*) ; 
 TYPE_1__ cpupower_cpu_info ; 
 int get_boost_mode_x86 (unsigned int) ; 
 int /*<<< orphan*/  print_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int get_boost_mode(unsigned int cpu)
{
	struct cpufreq_frequencies *freqs;

	if (cpupower_cpu_info.vendor == X86_VENDOR_AMD ||
	    cpupower_cpu_info.vendor == X86_VENDOR_HYGON ||
	    cpupower_cpu_info.vendor == X86_VENDOR_INTEL)
		return get_boost_mode_x86(cpu);

	freqs = cpufreq_get_frequencies("boost", cpu);
	if (freqs) {
		printf(_("  boost frequency steps: "));
		while (freqs->next) {
			print_speed(freqs->frequency);
			printf(", ");
			freqs = freqs->next;
		}
		print_speed(freqs->frequency);
		printf("\n");
		cpufreq_put_frequencies(freqs);
	}

	return 0;
}