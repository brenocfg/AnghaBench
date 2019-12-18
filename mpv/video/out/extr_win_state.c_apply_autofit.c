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
struct m_geometry {int /*<<< orphan*/  wh_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_geometry_apply (int*,int*,int*,int*,int,int,struct m_geometry*) ; 

__attribute__((used)) static void apply_autofit(int *w, int *h, int scr_w, int scr_h,
                          struct m_geometry *geo, bool allow_up, bool allow_down)
{
    if (!geo->wh_valid)
        return;

    int dummy = 0;
    int n_w = *w, n_h = *h;
    m_geometry_apply(&dummy, &dummy, &n_w, &n_h, scr_w, scr_h, geo);

    if (!allow_up && *w <= n_w && *h <= n_h)
        return;
    if (!allow_down && *w >= n_w && *h >= n_h)
        return;

    // If aspect mismatches, always make the window smaller than the fit box
    // (Or larger, if allow_down==false.)
    double asp = (double)*w / *h;
    double n_asp = (double)n_w / n_h;
    if ((n_asp <= asp) == allow_down) {
        *w = n_w;
        *h = n_w / asp;
    } else {
        *w = n_h * asp;
        *h = n_h;
    }
}