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
struct ar8xxx_priv {scalar_t__ chip_ver; } ;

/* Variables and functions */
 scalar_t__ AR8XXX_VER_AR8337 ; 

__attribute__((used)) static inline bool chip_is_ar8337(struct ar8xxx_priv *priv)
{
	return priv->chip_ver == AR8XXX_VER_AR8337;
}