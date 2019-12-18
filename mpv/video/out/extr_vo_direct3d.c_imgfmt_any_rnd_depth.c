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

/* Variables and functions */
 scalar_t__ IMGFMT_IS_RGB (int) ; 
 scalar_t__ IMGFMT_IS_Y (int) ; 
 int IMGFMT_RGB_DEPTH (int) ; 
 int IMGFMT_Y_DEPTH (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int imgfmt_any_rnd_depth(int fmt)
{
    if (IMGFMT_IS_RGB(fmt))
        return IMGFMT_RGB_DEPTH(fmt);
    if (IMGFMT_IS_Y(fmt))
        return IMGFMT_Y_DEPTH(fmt);
    assert(false);
    return 0;
}