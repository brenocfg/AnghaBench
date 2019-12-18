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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  MUTEX_TEXTURE1 ; 
 int /*<<< orphan*/  MUTEX_TEXTURE2 ; 
 scalar_t__ init_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* tex_mutexes ; 

__attribute__((used)) static inline bool init_mutexes(void)
{
	DWORD pid = GetCurrentProcessId();

	tex_mutexes[0] = init_mutex(MUTEX_TEXTURE1, pid);
	if (!tex_mutexes[0]) {
		return false;
	}

	tex_mutexes[1] = init_mutex(MUTEX_TEXTURE2, pid);
	if (!tex_mutexes[1]) {
		return false;
	}

	return true;
}