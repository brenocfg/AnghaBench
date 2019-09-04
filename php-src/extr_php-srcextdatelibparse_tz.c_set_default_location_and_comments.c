#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* comments; scalar_t__ longitude; scalar_t__ latitude; } ;
struct TYPE_5__ {TYPE_1__ location; } ;
typedef  TYPE_2__ timelib_tzinfo ;

/* Variables and functions */
 char* timelib_malloc (int) ; 

__attribute__((used)) static void set_default_location_and_comments(const unsigned char **tzf, timelib_tzinfo *tz)
{
	tz->location.latitude = 0;
	tz->location.longitude = 0;
	tz->location.comments = timelib_malloc(2);
	tz->location.comments[0] = '?';
	tz->location.comments[1] = '\0';
}