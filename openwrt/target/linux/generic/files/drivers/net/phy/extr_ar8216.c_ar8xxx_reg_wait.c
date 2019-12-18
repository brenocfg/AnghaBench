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
typedef  int u32 ;
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int ar8xxx_read (struct ar8xxx_priv*,int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
ar8xxx_reg_wait(struct ar8xxx_priv *priv, u32 reg, u32 mask, u32 val,
		unsigned timeout)
{
	int i;

	for (i = 0; i < timeout; i++) {
		u32 t;

		t = ar8xxx_read(priv, reg);
		if ((t & mask) == val)
			return 0;

		usleep_range(1000, 2000);
		cond_resched();
	}

	return -ETIMEDOUT;
}