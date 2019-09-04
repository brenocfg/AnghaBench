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
struct ak4613_formats {unsigned int fmt; unsigned int width; } ;
struct ak4613_interface {struct ak4613_formats capture; struct ak4613_formats playback; } ;

/* Variables and functions */

__attribute__((used)) static bool ak4613_dai_fmt_matching(const struct ak4613_interface *iface,
				    int is_play,
				    unsigned int fmt, unsigned int width)
{
	const struct ak4613_formats *fmts;

	fmts = (is_play) ? &iface->playback : &iface->capture;

	if (fmts->fmt != fmt)
		return false;

	if (fmts->width != width)
		return false;

	return true;
}