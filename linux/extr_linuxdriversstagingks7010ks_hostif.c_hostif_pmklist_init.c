#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pmk; int /*<<< orphan*/  head; } ;
struct ks_wlan_private {TYPE_2__ pmklist; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PMK_LIST_MAX ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hostif_pmklist_init(struct ks_wlan_private *priv)
{
	int i;

	memset(&priv->pmklist, 0, sizeof(priv->pmklist));
	INIT_LIST_HEAD(&priv->pmklist.head);
	for (i = 0; i < PMK_LIST_MAX; i++)
		INIT_LIST_HEAD(&priv->pmklist.pmk[i].list);
}