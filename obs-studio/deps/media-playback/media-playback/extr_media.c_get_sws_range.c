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
typedef  enum AVColorRange { ____Placeholder_AVColorRange } AVColorRange ;

/* Variables and functions */
 int AVCOL_RANGE_JPEG ; 

__attribute__((used)) static inline int get_sws_range(enum AVColorRange r)
{
	return r == AVCOL_RANGE_JPEG ? 1 : 0;
}