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
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct coda_timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static struct coda_timespec timespec64_to_coda(struct timespec64 ts64)
{
	struct coda_timespec ts = {
		.tv_sec = ts64.tv_sec,
		.tv_nsec = ts64.tv_nsec,
	};

	return ts;
}