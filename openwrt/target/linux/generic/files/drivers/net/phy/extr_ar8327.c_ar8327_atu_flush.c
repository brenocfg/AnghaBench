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
 int AR8327_ATU_FUNC_BUSY ; 
 int AR8327_ATU_FUNC_OP_FLUSH ; 
 int /*<<< orphan*/  AR8327_REG_ATU_FUNC ; 
 int ar8216_wait_bit (struct ar8xxx_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8327_atu_flush(struct ar8xxx_priv *priv)
{
	int ret;

	ret = ar8216_wait_bit(priv, AR8327_REG_ATU_FUNC,
			      AR8327_ATU_FUNC_BUSY, 0);
	if (!ret)
		ar8xxx_write(priv, AR8327_REG_ATU_FUNC,
			     AR8327_ATU_FUNC_OP_FLUSH |
			     AR8327_ATU_FUNC_BUSY);

	return ret;
}