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
struct j1939_priv {int /*<<< orphan*/  ecus; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct j1939_ecu {int /*<<< orphan*/  list; struct j1939_priv* priv; TYPE_1__ ac_timer; int /*<<< orphan*/  name; int /*<<< orphan*/  addr; int /*<<< orphan*/  kref; } ;
typedef  int /*<<< orphan*/  name_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct j1939_ecu* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_SOFT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  J1939_IDLE_ADDR ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_ecu_timer_handler ; 
 int /*<<< orphan*/  j1939_priv_get (struct j1939_priv*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct j1939_ecu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

struct j1939_ecu *j1939_ecu_create_locked(struct j1939_priv *priv, name_t name)
{
	struct j1939_ecu *ecu;

	lockdep_assert_held(&priv->lock);

	ecu = kzalloc(sizeof(*ecu), gfp_any());
	if (!ecu)
		return ERR_PTR(-ENOMEM);
	kref_init(&ecu->kref);
	ecu->addr = J1939_IDLE_ADDR;
	ecu->name = name;

	hrtimer_init(&ecu->ac_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL_SOFT);
	ecu->ac_timer.function = j1939_ecu_timer_handler;
	INIT_LIST_HEAD(&ecu->list);

	j1939_priv_get(priv);
	ecu->priv = priv;
	list_add_tail(&ecu->list, &priv->ecus);

	return ecu;
}