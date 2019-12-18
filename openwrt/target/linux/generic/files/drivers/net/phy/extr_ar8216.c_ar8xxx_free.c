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
struct ar8xxx_priv {struct ar8xxx_priv* mib_stats; struct ar8xxx_priv* chip_data; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct ar8xxx_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ar8xxx_priv*) ; 

__attribute__((used)) static void
ar8xxx_free(struct ar8xxx_priv *priv)
{
	if (priv->chip && priv->chip->cleanup)
		priv->chip->cleanup(priv);

	kfree(priv->chip_data);
	kfree(priv->mib_stats);
	kfree(priv);
}