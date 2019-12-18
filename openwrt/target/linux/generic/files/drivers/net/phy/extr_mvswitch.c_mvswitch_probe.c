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
struct phy_device {struct mvswitch_priv* priv; } ;
struct mvswitch_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mvswitch_priv* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvswitch_probe(struct phy_device *pdev)
{
	struct mvswitch_priv *priv;

	priv = kzalloc(sizeof(struct mvswitch_priv), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	pdev->priv = priv;

	return 0;
}