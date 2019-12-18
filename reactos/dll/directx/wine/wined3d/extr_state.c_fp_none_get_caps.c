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
struct wined3d_gl_info {int dummy; } ;
struct fragment_caps {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct fragment_caps*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fp_none_get_caps(const struct wined3d_gl_info *gl_info, struct fragment_caps *caps)
{
    memset(caps, 0, sizeof(*caps));
}