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
struct fb_var_screeninfo {int dummy; } ;
struct fb_par_valkyrie {int /*<<< orphan*/  cmode; int /*<<< orphan*/  vmode; } ;

/* Variables and functions */
 int mac_vmode_to_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fb_var_screeninfo*) ; 

__attribute__((used)) static inline int valkyrie_par_to_var(struct fb_par_valkyrie *par,
				      struct fb_var_screeninfo *var)
{
	return mac_vmode_to_var(par->vmode, par->cmode, var);
}