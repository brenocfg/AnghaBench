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
struct v4l2_queryctrl {int dummy; } ;

/* Variables and functions */
 int maven_get_queryctrl (void*,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int maven_out_get_queryctrl(void* md, struct v4l2_queryctrl* p) {
        return maven_get_queryctrl(md, p);
}