#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ra_buf_params {int dummy; } ;
struct ra_buf {int dummy; } ;
struct ra {TYPE_1__* fns; } ;
struct TYPE_2__ {struct ra_buf* (* buf_create ) (struct ra*,struct ra_buf_params const*) ;} ;

/* Variables and functions */
 struct ra_buf* stub1 (struct ra*,struct ra_buf_params const*) ; 

struct ra_buf *ra_buf_create(struct ra *ra, const struct ra_buf_params *params)
{
    return ra->fns->buf_create(ra, params);
}