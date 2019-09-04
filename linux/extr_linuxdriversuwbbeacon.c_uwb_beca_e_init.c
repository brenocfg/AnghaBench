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
struct uwb_beca_e {int /*<<< orphan*/  rssi_stats; int /*<<< orphan*/  lqe_stats; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uwb_beca_e_init(struct uwb_beca_e *bce)
{
	mutex_init(&bce->mutex);
	kref_init(&bce->refcnt);
	stats_init(&bce->lqe_stats);
	stats_init(&bce->rssi_stats);
}