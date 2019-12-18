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
struct sun4i_i2s {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static s8 sun4i_i2s_get_wss(const struct sun4i_i2s *i2s, int width)
{
	if (width < 16 || width > 32)
		return -EINVAL;

	if (width % 4)
		return -EINVAL;

	return (width - 16) / 4;
}