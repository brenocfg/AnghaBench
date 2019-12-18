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

/* Variables and functions */
 int AV_LOG_INFO ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  blogva (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmpeg_log_callback(void *param, int level, const char *format,
				va_list args)
{
	if (level <= AV_LOG_INFO)
		blogva(LOG_DEBUG, format, args);

	UNUSED_PARAMETER(param);
}