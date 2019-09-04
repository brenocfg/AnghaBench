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
struct uvcg_uncompressed {int dummy; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uvcg_uncompressed*) ; 
 struct uvcg_uncompressed* to_uvcg_uncompressed (struct config_item*) ; 

__attribute__((used)) static void uvcg_uncompressed_drop(struct config_group *group,
			    struct config_item *item)
{
	struct uvcg_uncompressed *h = to_uvcg_uncompressed(item);

	kfree(h);
}