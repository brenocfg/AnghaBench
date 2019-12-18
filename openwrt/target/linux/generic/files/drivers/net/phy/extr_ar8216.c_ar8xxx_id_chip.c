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
struct ar8xxx_priv {int chip_ver; int /*<<< orphan*/  chip_rev; int /*<<< orphan*/ * chip; } ;

/* Variables and functions */
#define  AR8XXX_VER_AR8216 132 
#define  AR8XXX_VER_AR8236 131 
#define  AR8XXX_VER_AR8316 130 
#define  AR8XXX_VER_AR8327 129 
#define  AR8XXX_VER_AR8337 128 
 int ENODEV ; 
 int /*<<< orphan*/  ar8216_chip ; 
 int /*<<< orphan*/  ar8236_chip ; 
 int /*<<< orphan*/  ar8316_chip ; 
 int /*<<< orphan*/  ar8327_chip ; 
 int /*<<< orphan*/  ar8337_chip ; 
 int ar8xxx_read_id (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8xxx_id_chip(struct ar8xxx_priv *priv)
{
	int ret;

	ret = ar8xxx_read_id(priv);
	if(ret)
		return ret;

	switch (priv->chip_ver) {
	case AR8XXX_VER_AR8216:
		priv->chip = &ar8216_chip;
		break;
	case AR8XXX_VER_AR8236:
		priv->chip = &ar8236_chip;
		break;
	case AR8XXX_VER_AR8316:
		priv->chip = &ar8316_chip;
		break;
	case AR8XXX_VER_AR8327:
		priv->chip = &ar8327_chip;
		break;
	case AR8XXX_VER_AR8337:
		priv->chip = &ar8337_chip;
		break;
	default:
		pr_err("ar8216: Unknown Atheros device [ver=%d, rev=%d]\n",
		       priv->chip_ver, priv->chip_rev);

		return -ENODEV;
	}

	return 0;
}