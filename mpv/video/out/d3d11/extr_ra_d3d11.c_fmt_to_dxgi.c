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
struct ra_format {struct d3d_fmt* priv; } ;
struct d3d_fmt {int /*<<< orphan*/  fmt; } ;
typedef  int /*<<< orphan*/  DXGI_FORMAT ;

/* Variables and functions */

__attribute__((used)) static DXGI_FORMAT fmt_to_dxgi(const struct ra_format *fmt)
{
    struct d3d_fmt *d3d = fmt->priv;
    return d3d->fmt;
}