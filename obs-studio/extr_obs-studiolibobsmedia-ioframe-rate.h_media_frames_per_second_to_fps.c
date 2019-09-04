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
struct media_frames_per_second {double denominator; scalar_t__ numerator; } ;

/* Variables and functions */

__attribute__((used)) static inline double media_frames_per_second_to_fps(
		struct media_frames_per_second fps)
{
	return (double)fps.numerator / fps.denominator;
}