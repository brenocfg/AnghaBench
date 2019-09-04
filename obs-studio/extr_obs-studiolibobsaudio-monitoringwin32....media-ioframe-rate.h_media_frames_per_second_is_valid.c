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
struct media_frames_per_second {scalar_t__ denominator; scalar_t__ numerator; } ;

/* Variables and functions */

__attribute__((used)) static inline bool media_frames_per_second_is_valid(
		struct media_frames_per_second fps)
{
	return fps.numerator && fps.denominator;
}