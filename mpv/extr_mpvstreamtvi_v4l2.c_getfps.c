#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double numerator; scalar_t__ denominator; } ;
struct TYPE_7__ {TYPE_3__ frameperiod; } ;
struct TYPE_9__ {TYPE_2__ standard; TYPE_1__* tv_param; } ;
typedef  TYPE_4__ priv_t ;
struct TYPE_6__ {scalar_t__ fps; } ;

/* Variables and functions */

__attribute__((used)) static double getfps(priv_t *priv)
{
    if (priv->tv_param->fps > 0)
        return priv->tv_param->fps;
    if (priv->standard.frameperiod.denominator && priv->standard.frameperiod.numerator)
        return (double)priv->standard.frameperiod.denominator / priv->standard.frameperiod.numerator;
    return 25.0;
}