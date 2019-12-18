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
struct evea_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evea_update_switch_hp (struct evea_priv*) ; 
 int /*<<< orphan*/  evea_update_switch_lin (struct evea_priv*) ; 
 int /*<<< orphan*/  evea_update_switch_lo (struct evea_priv*) ; 

__attribute__((used)) static void evea_update_switch_all(struct evea_priv *evea)
{
	evea_update_switch_lin(evea);
	evea_update_switch_lo(evea);
	evea_update_switch_hp(evea);
}