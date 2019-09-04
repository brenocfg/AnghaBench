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
struct rocker {struct ofdpa* wpriv; } ;
struct ofdpa {int /*<<< orphan*/  ageing_time; int /*<<< orphan*/  fdb_cleanup_timer; int /*<<< orphan*/  neigh_tbl_lock; int /*<<< orphan*/  neigh_tbl; int /*<<< orphan*/  internal_vlan_tbl_lock; int /*<<< orphan*/  internal_vlan_tbl; int /*<<< orphan*/  fdb_tbl_lock; int /*<<< orphan*/  fdb_tbl; int /*<<< orphan*/  group_tbl_lock; int /*<<< orphan*/  group_tbl; int /*<<< orphan*/  flow_tbl_lock; int /*<<< orphan*/  flow_tbl; struct rocker* rocker; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_DEFAULT_AGEING_TIME ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_fdb_cleanup ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_init(struct rocker *rocker)
{
	struct ofdpa *ofdpa = rocker->wpriv;

	ofdpa->rocker = rocker;

	hash_init(ofdpa->flow_tbl);
	spin_lock_init(&ofdpa->flow_tbl_lock);

	hash_init(ofdpa->group_tbl);
	spin_lock_init(&ofdpa->group_tbl_lock);

	hash_init(ofdpa->fdb_tbl);
	spin_lock_init(&ofdpa->fdb_tbl_lock);

	hash_init(ofdpa->internal_vlan_tbl);
	spin_lock_init(&ofdpa->internal_vlan_tbl_lock);

	hash_init(ofdpa->neigh_tbl);
	spin_lock_init(&ofdpa->neigh_tbl_lock);

	timer_setup(&ofdpa->fdb_cleanup_timer, ofdpa_fdb_cleanup, 0);
	mod_timer(&ofdpa->fdb_cleanup_timer, jiffies);

	ofdpa->ageing_time = BR_DEFAULT_AGEING_TIME;

	return 0;
}