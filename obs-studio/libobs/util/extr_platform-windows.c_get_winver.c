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
typedef  int uint32_t ;
struct win_version_info {int major; int minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_win_ver (struct win_version_info*) ; 
 int winver ; 

__attribute__((used)) static inline uint32_t get_winver(void)
{
	if (!winver) {
		struct win_version_info ver;
		get_win_ver(&ver);
		winver = (ver.major << 8) | ver.minor;
	}

	return winver;
}