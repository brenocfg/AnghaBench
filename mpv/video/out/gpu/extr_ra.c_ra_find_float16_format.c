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
struct ra_format {int dummy; } ;
struct ra {int dummy; } ;

/* Variables and functions */
 struct ra_format const* ra_find_float_format (struct ra*,int,int) ; 

const struct ra_format *ra_find_float16_format(struct ra *ra, int n_components)
{
    return ra_find_float_format(ra, sizeof(float), n_components);
}