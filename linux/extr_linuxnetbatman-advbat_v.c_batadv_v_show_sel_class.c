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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sel_class; } ;
struct batadv_priv {TYPE_1__ gw; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t batadv_v_show_sel_class(struct batadv_priv *bat_priv, char *buff)
{
	u32 class = atomic_read(&bat_priv->gw.sel_class);

	return sprintf(buff, "%u.%u MBit\n", class / 10, class % 10);
}