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
struct reset_controller_dev {int dummy; } ;
struct berlin_reset_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BIT (unsigned long) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 
 struct berlin_reset_priv* to_berlin_reset_priv (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int berlin_reset_reset(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	struct berlin_reset_priv *priv = to_berlin_reset_priv(rcdev);
	int offset = id >> 8;
	int mask = BIT(id & 0x1f);

	regmap_write(priv->regmap, offset, mask);

	/* let the reset be effective */
	udelay(10);

	return 0;
}