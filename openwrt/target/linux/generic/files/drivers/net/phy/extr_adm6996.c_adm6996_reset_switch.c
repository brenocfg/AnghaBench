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
struct switch_dev {int dummy; } ;
struct adm6996_priv {int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  adm6996_perform_reset (struct adm6996_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 struct adm6996_priv* to_adm (struct switch_dev*) ; 

__attribute__((used)) static int
adm6996_reset_switch(struct switch_dev *dev)
{
	struct adm6996_priv *priv = to_adm(dev);

	pr_devel("reset\n");

	mutex_lock(&priv->reg_mutex);
	adm6996_perform_reset (priv);
	mutex_unlock(&priv->reg_mutex);
	return 0;
}