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
struct work_struct {int dummy; } ;
struct o2net_sock_container {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  o2net_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 int /*<<< orphan*/  sc_get (struct o2net_sock_container*) ; 
 int /*<<< orphan*/  sc_put (struct o2net_sock_container*) ; 

__attribute__((used)) static void o2net_sc_queue_work(struct o2net_sock_container *sc,
				struct work_struct *work)
{
	sc_get(sc);
	if (!queue_work(o2net_wq, work))
		sc_put(sc);
}