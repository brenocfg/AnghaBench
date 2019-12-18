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
struct rfcomm_dlc {unsigned int mtu; } ;
struct rfcomm_dev {int /*<<< orphan*/  wmem_alloc; struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned int rfcomm_room(struct rfcomm_dev *dev)
{
	struct rfcomm_dlc *dlc = dev->dlc;

	/* Limit the outstanding number of packets not yet sent to 40 */
	int pending = 40 - atomic_read(&dev->wmem_alloc);

	return max(0, pending) * dlc->mtu;
}