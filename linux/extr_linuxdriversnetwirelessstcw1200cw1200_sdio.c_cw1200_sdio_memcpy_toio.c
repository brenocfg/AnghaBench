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
 int sdio_memcpy_toio (int /*<<< orphan*/ ,unsigned int,void*,int) ; 

__attribute__((used)) static int cw1200_sdio_memcpy_toio(struct hwbus_priv *self,
				   unsigned int addr,
				   const void *src, int count)
{
	return sdio_memcpy_toio(self->func, addr, (void *)src, count);
}