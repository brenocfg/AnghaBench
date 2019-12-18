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
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 

void* platform_print_deprecation_note( const char *msg, const char *time_frame)
{
  printf( "Warning, deprecated API! %s. It will be removed %s. See documentation for details.\n", msg, time_frame );
}