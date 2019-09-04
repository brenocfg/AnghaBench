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
struct msm6242_priv {int dummy; } ;

/* Variables and functions */
 unsigned int msm6242_read (struct msm6242_priv*,unsigned int) ; 
 int /*<<< orphan*/  msm6242_write (struct msm6242_priv*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void msm6242_set(struct msm6242_priv *priv, unsigned int val,
			       unsigned int reg)
{
	msm6242_write(priv, msm6242_read(priv, reg) | val, reg);
}