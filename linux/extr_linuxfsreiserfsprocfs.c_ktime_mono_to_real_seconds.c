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
typedef  int /*<<< orphan*/  time64_t ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  ktime_divns (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_mono_to_real (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static time64_t ktime_mono_to_real_seconds(time64_t mono)
{
	ktime_t kt = ktime_set(mono, NSEC_PER_SEC/2);

	return ktime_divns(ktime_mono_to_real(kt), NSEC_PER_SEC);
}