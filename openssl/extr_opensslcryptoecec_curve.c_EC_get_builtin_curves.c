#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  comment; int /*<<< orphan*/  nid; } ;
struct TYPE_4__ {int /*<<< orphan*/  comment; int /*<<< orphan*/  nid; } ;
typedef  TYPE_1__ EC_builtin_curve ;

/* Variables and functions */
 TYPE_2__* curve_list ; 
 size_t curve_list_length ; 

size_t EC_get_builtin_curves(EC_builtin_curve *r, size_t nitems)
{
    size_t i, min;

    if (r == NULL || nitems == 0)
        return curve_list_length;

    min = nitems < curve_list_length ? nitems : curve_list_length;

    for (i = 0; i < min; i++) {
        r[i].nid = curve_list[i].nid;
        r[i].comment = curve_list[i].comment;
    }

    return curve_list_length;
}