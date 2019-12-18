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
struct madera_priv {int /*<<< orphan*/ * domain_group_ref; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void madera_debug_dump_domain_groups(const struct madera_priv *priv)
{
	struct madera *madera = priv->madera;
	int i;

	for (i = 0; i < ARRAY_SIZE(priv->domain_group_ref); ++i)
		dev_dbg(madera->dev, "domain_grp_ref[%d]=%d\n", i,
			priv->domain_group_ref[i]);
}