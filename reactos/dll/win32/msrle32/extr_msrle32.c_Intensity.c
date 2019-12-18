#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_3__ {int rgbRed; int rgbGreen; int rgbBlue; } ;
typedef  TYPE_1__ RGBQUAD ;

/* Variables and functions */

__attribute__((used)) static inline WORD Intensity(RGBQUAD clr)
{
  return (30 * clr.rgbRed + 59 * clr.rgbGreen + 11 * clr.rgbBlue)/4;
}