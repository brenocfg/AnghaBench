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
struct rio_net {scalar_t__ enum_data; } ;
struct rio_id_table {int max; int /*<<< orphan*/  lock; scalar_t__ start; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int RIO_INVALID_DESTID ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 rio_destid_next(struct rio_net *net, u16 from)
{
	int destid;
	struct rio_id_table *idtab = (struct rio_id_table *)net->enum_data;

	spin_lock(&idtab->lock);
	destid = find_next_bit(idtab->table, idtab->max, from);
	if (destid >= idtab->max)
		destid = RIO_INVALID_DESTID;
	else
		destid += idtab->start;
	spin_unlock(&idtab->lock);
	return (u16)destid;
}