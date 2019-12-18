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
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_GCTRL_MTU ; 
 int /*<<< orphan*/  AR8216_REG_GLOBAL_CTRL ; 
 int /*<<< orphan*/  ar8xxx_rmw (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int,int) ; 

__attribute__((used)) static void
ar8216_init_globals(struct ar8xxx_priv *priv)
{
	/* standard atheros magic */
	ar8xxx_write(priv, 0x38, 0xc000050e);

	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
		   AR8216_GCTRL_MTU, 1518 + 8 + 2);
}