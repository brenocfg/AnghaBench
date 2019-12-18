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
struct mp_colorspace {scalar_t__ light; scalar_t__ sig_peak; scalar_t__ gamma; scalar_t__ primaries; scalar_t__ levels; scalar_t__ space; } ;

/* Variables and functions */

void mp_colorspace_merge(struct mp_colorspace *orig, struct mp_colorspace *new)
{
    if (!orig->space)
        orig->space = new->space;
    if (!orig->levels)
        orig->levels = new->levels;
    if (!orig->primaries)
        orig->primaries = new->primaries;
    if (!orig->gamma)
        orig->gamma = new->gamma;
    if (!orig->sig_peak)
        orig->sig_peak = new->sig_peak;
    if (!orig->light)
        orig->light = new->light;
}