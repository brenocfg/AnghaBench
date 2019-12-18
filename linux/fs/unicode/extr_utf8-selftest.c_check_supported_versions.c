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
 int latest_maj ; 
 int latest_min ; 
 int latest_rev ; 
 int /*<<< orphan*/  test (int) ; 
 int utf8version_is_supported (int,int,int) ; 

__attribute__((used)) static void check_supported_versions(void)
{
	/* Unicode 7.0.0 should be supported. */
	test(utf8version_is_supported(7, 0, 0));

	/* Unicode 9.0.0 should be supported. */
	test(utf8version_is_supported(9, 0, 0));

	/* Unicode 1x.0.0 (the latest version) should be supported. */
	test(utf8version_is_supported(latest_maj, latest_min, latest_rev));

	/* Next versions don't exist. */
	test(!utf8version_is_supported(13, 0, 0));
	test(!utf8version_is_supported(0, 0, 0));
	test(!utf8version_is_supported(-1, -1, -1));
}