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
struct win_version_info {int /*<<< orphan*/  revis; int /*<<< orphan*/  build; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_win_ver (struct win_version_info*) ; 
 int is_64_bit_windows () ; 

__attribute__((used)) static void log_windows_version(void)
{
	struct win_version_info ver;
	get_win_ver(&ver);

	bool b64 = is_64_bit_windows();
	const char *windows_bitness = b64 ? "64" : "32";

	blog(LOG_INFO, "Windows Version: %d.%d Build %d (revision: %d; %s-bit)",
	     ver.major, ver.minor, ver.build, ver.revis, windows_bitness);
}