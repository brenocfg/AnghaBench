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
struct colormap {int /*<<< orphan*/  max; } ;
typedef  int /*<<< orphan*/  color ;

/* Variables and functions */
 scalar_t__ CISERR () ; 
 int /*<<< orphan*/  COLORLESS ; 

__attribute__((used)) static color
maxcolor(struct colormap *cm)
{
	if (CISERR())
		return COLORLESS;

	return (color) cm->max;
}