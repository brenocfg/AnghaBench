#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct w5100_priv {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  W5100_IMR ; 
 scalar_t__ W5500 ; 
 int /*<<< orphan*/  W5500_SIMR ; 
 int /*<<< orphan*/  w5100_write (struct w5100_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w5100_socket_intr_mask(struct w5100_priv *priv, u8 mask)
{
	u32 imr;

	if (priv->ops->chip_id == W5500)
		imr = W5500_SIMR;
	else
		imr = W5100_IMR;

	w5100_write(priv, imr, mask);
}