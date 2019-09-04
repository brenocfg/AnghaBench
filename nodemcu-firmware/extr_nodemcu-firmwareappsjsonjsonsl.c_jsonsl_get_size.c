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
struct jsonsl_state_st {int dummy; } ;
struct jsonsl_st {int dummy; } ;

/* Variables and functions */

size_t jsonsl_get_size(int nlevels)
{
    return sizeof (struct jsonsl_st) + ( (nlevels-1) * sizeof (struct jsonsl_state_st)) ;
}