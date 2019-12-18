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
struct ar8xxx_priv {TYPE_1__* chip; } ;
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int AR8XXX_CAP_GIGE ; 

__attribute__((used)) static inline bool ar8xxx_has_gige(struct ar8xxx_priv *priv)
{
	return priv->chip->caps & AR8XXX_CAP_GIGE;
}