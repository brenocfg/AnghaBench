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
struct gl_video {int /*<<< orphan*/  cms; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 scalar_t__ gl_lcms_set_memory_profile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_from_options (struct gl_video*) ; 

void gl_video_set_icc_profile(struct gl_video *p, bstr icc_data)
{
    if (gl_lcms_set_memory_profile(p->cms, icc_data))
        reinit_from_options(p);
}