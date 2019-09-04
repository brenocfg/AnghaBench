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
struct gntdev_priv {int /*<<< orphan*/  lock; } ;
struct gntdev_grant_map {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  gntdev_put_map (int /*<<< orphan*/ *,struct gntdev_grant_map*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmabuf_exp_remove_map(struct gntdev_priv *priv,
				  struct gntdev_grant_map *map)
{
	mutex_lock(&priv->lock);
	list_del(&map->next);
	gntdev_put_map(NULL /* already removed */, map);
	mutex_unlock(&priv->lock);
}