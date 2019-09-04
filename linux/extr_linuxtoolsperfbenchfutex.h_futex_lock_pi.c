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
typedef  int /*<<< orphan*/  u_int32_t ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUTEX_LOCK_PI ; 
 int futex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
futex_lock_pi(u_int32_t *uaddr, struct timespec *timeout, int opflags)
{
	return futex(uaddr, FUTEX_LOCK_PI, 0, timeout, NULL, 0, opflags);
}