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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  device_path ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_heads_path ; 
 int /*<<< orphan*/  write_int (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void protect(int seconds)
{
	const char *str = (seconds == 0) ? "Unparked" : "Parked";

	write_int(unload_heads_path, seconds*1000);
	syslog(LOG_INFO, "%s %s disk head\n", str, device_path);
}