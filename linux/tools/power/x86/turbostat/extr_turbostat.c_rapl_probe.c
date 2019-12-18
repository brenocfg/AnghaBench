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
 scalar_t__ authentic_amd ; 
 scalar_t__ genuine_intel ; 
 scalar_t__ hygon_genuine ; 
 int /*<<< orphan*/  rapl_probe_amd (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rapl_probe_intel (unsigned int,unsigned int) ; 

void rapl_probe(unsigned int family, unsigned int model)
{
	if (genuine_intel)
		rapl_probe_intel(family, model);
	if (authentic_amd || hygon_genuine)
		rapl_probe_amd(family, model);
}