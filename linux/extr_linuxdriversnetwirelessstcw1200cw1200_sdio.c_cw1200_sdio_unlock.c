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
struct hwbus_priv {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cw1200_sdio_unlock(struct hwbus_priv *self)
{
	sdio_release_host(self->func);
}