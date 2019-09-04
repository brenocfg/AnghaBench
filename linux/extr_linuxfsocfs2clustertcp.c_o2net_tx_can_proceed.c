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
struct o2net_sock_container {int /*<<< orphan*/  sc_kref; } ;
struct o2net_node {int nn_persistent_error; int /*<<< orphan*/  nn_lock; struct o2net_sock_container* nn_sc; scalar_t__ nn_sc_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2net_tx_can_proceed(struct o2net_node *nn,
			        struct o2net_sock_container **sc_ret,
				int *error)
{
	int ret = 0;

	spin_lock(&nn->nn_lock);
	if (nn->nn_persistent_error) {
		ret = 1;
		*sc_ret = NULL;
		*error = nn->nn_persistent_error;
	} else if (nn->nn_sc_valid) {
		kref_get(&nn->nn_sc->sc_kref);

		ret = 1;
		*sc_ret = nn->nn_sc;
		*error = 0;
	}
	spin_unlock(&nn->nn_lock);

	return ret;
}