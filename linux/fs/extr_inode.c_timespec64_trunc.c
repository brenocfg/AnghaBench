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
struct timespec64 {unsigned int tv_nsec; } ;

/* Variables and functions */
 unsigned int NSEC_PER_SEC ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 

struct timespec64 timespec64_trunc(struct timespec64 t, unsigned gran)
{
	/* Avoid division in the common cases 1 ns and 1 s. */
	if (gran == 1) {
		/* nothing */
	} else if (gran == NSEC_PER_SEC) {
		t.tv_nsec = 0;
	} else if (gran > 1 && gran < NSEC_PER_SEC) {
		t.tv_nsec -= t.tv_nsec % gran;
	} else {
		WARN(1, "illegal file time granularity: %u", gran);
	}
	return t;
}