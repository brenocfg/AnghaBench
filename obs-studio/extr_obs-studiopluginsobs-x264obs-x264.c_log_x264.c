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
typedef  int /*<<< orphan*/  va_list ;
struct obs_x264 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_x264(void *param, int level, const char *format, va_list args)
{
	struct obs_x264 *obsx264 = param;
	char str[1024];

	vsnprintf(str, 1024, format, args);
	info("%s", str);

	UNUSED_PARAMETER(level);
}