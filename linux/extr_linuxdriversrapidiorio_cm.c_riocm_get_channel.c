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
typedef  int /*<<< orphan*/  u16 ;
struct rio_channel {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ch_idr ; 
 struct rio_channel* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rio_channel *riocm_get_channel(u16 nr)
{
	struct rio_channel *ch;

	spin_lock_bh(&idr_lock);
	ch = idr_find(&ch_idr, nr);
	if (ch)
		kref_get(&ch->ref);
	spin_unlock_bh(&idr_lock);
	return ch;
}