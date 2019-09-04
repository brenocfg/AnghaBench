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
struct per_user_data {int nr_evtchns; int ring_size; int /*<<< orphan*/  ring_cons_mutex; int /*<<< orphan*/  ring_prod_lock; int /*<<< orphan*/ * ring; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  evtchn_free_ring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evtchn_resize_ring(struct per_user_data *u)
{
	unsigned int new_size;
	evtchn_port_t *new_ring, *old_ring;

	/*
	 * Ensure the ring is large enough to capture all possible
	 * events. i.e., one free slot for each bound event.
	 */
	if (u->nr_evtchns <= u->ring_size)
		return 0;

	if (u->ring_size == 0)
		new_size = 64;
	else
		new_size = 2 * u->ring_size;

	new_ring = kvmalloc_array(new_size, sizeof(*new_ring), GFP_KERNEL);
	if (!new_ring)
		return -ENOMEM;

	old_ring = u->ring;

	/*
	 * Access to the ring contents is serialized by either the
	 * prod /or/ cons lock so take both when resizing.
	 */
	mutex_lock(&u->ring_cons_mutex);
	spin_lock_irq(&u->ring_prod_lock);

	/*
	 * Copy the old ring contents to the new ring.
	 *
	 * To take care of wrapping, a full ring, and the new index
	 * pointing into the second half, simply copy the old contents
	 * twice.
	 *
	 * +---------+    +------------------+
	 * |34567  12| -> |34567  1234567  12|
	 * +-----p-c-+    +-------c------p---+
	 */
	memcpy(new_ring, old_ring, u->ring_size * sizeof(*u->ring));
	memcpy(new_ring + u->ring_size, old_ring,
	       u->ring_size * sizeof(*u->ring));

	u->ring = new_ring;
	u->ring_size = new_size;

	spin_unlock_irq(&u->ring_prod_lock);
	mutex_unlock(&u->ring_cons_mutex);

	evtchn_free_ring(old_ring);

	return 0;
}