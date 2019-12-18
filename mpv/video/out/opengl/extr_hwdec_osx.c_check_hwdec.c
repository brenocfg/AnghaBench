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
struct ra_hwdec {int /*<<< orphan*/  ra; } ;
struct TYPE_3__ {int version; } ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  CGLGetCurrentContext () ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec*,char*) ; 
 TYPE_1__* ra_gl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_is_gl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_hwdec(struct ra_hwdec *hw)
{
    if (!ra_is_gl(hw->ra))
        return false;

    GL *gl = ra_gl_get(hw->ra);
    if (gl->version < 300) {
        MP_ERR(hw, "need >= OpenGL 3.0 for core rectangle texture support\n");
        return false;
    }

    if (!CGLGetCurrentContext()) {
        MP_ERR(hw, "need cocoa opengl backend to be active");
        return false;
    }

    return true;
}