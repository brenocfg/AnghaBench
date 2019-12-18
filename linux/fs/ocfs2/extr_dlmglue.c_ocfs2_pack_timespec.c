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
typedef  int u64 ;
typedef  int u32 ;
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int OCFS2_NSEC_MASK ; 
 int OCFS2_SEC_SHIFT ; 
 int clamp_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time64_t ; 

__attribute__((used)) static u64 ocfs2_pack_timespec(struct timespec64 *spec)
{
	u64 res;
	u64 sec = clamp_t(time64_t, spec->tv_sec, 0, 0x3ffffffffull);
	u32 nsec = spec->tv_nsec;

	res = (sec << OCFS2_SEC_SHIFT) | (nsec & OCFS2_NSEC_MASK);

	return res;
}