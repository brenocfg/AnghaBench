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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ __intel_pt_pgd_ip (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool intel_pt_pgd_ip(uint64_t ip, void *data)
{
	return __intel_pt_pgd_ip(ip, data) > 0;
}