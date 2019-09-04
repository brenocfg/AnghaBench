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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT202X_REQUIRED_DEVS ; 
 int ef4_mdio_links_ok (struct ef4_nic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt202x_link_ok(struct ef4_nic *efx)
{
	return ef4_mdio_links_ok(efx, QT202X_REQUIRED_DEVS);
}