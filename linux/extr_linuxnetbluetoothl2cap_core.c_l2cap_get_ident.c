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
typedef  int u8 ;
struct l2cap_conn {int tx_ident; int /*<<< orphan*/  ident_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 l2cap_get_ident(struct l2cap_conn *conn)
{
	u8 id;

	/* Get next available identificator.
	 *    1 - 128 are used by kernel.
	 *  129 - 199 are reserved.
	 *  200 - 254 are used by utilities like l2ping, etc.
	 */

	mutex_lock(&conn->ident_lock);

	if (++conn->tx_ident > 128)
		conn->tx_ident = 1;

	id = conn->tx_ident;

	mutex_unlock(&conn->ident_lock);

	return id;
}