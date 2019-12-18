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
struct obs_x264 {int dummy; } ;

/* Variables and functions */
 char* validate (struct obs_x264*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x264_preset_names ; 

__attribute__((used)) static inline const char *validate_preset(struct obs_x264 *obsx264,
					  const char *preset)
{
	const char *new_preset =
		validate(obsx264, preset, "preset", x264_preset_names);
	return new_preset ? new_preset : "veryfast";
}