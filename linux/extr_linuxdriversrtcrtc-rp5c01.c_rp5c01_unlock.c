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
struct rp5c01_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP5C01_MODE ; 
 int RP5C01_MODE_MODE01 ; 
 int RP5C01_MODE_TIMER_EN ; 
 int /*<<< orphan*/  rp5c01_write (struct rp5c01_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rp5c01_unlock(struct rp5c01_priv *priv)
{
	rp5c01_write(priv, RP5C01_MODE_TIMER_EN | RP5C01_MODE_MODE01,
		     RP5C01_MODE);
}