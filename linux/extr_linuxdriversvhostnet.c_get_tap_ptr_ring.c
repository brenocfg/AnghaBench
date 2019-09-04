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
struct ptr_ring {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct ptr_ring*) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct ptr_ring* tap_get_ptr_ring (struct file*) ; 
 struct ptr_ring* tun_get_tx_ring (struct file*) ; 

__attribute__((used)) static struct ptr_ring *get_tap_ptr_ring(int fd)
{
	struct ptr_ring *ring;
	struct file *file = fget(fd);

	if (!file)
		return NULL;
	ring = tun_get_tx_ring(file);
	if (!IS_ERR(ring))
		goto out;
	ring = tap_get_ptr_ring(file);
	if (!IS_ERR(ring))
		goto out;
	ring = NULL;
out:
	fput(file);
	return ring;
}