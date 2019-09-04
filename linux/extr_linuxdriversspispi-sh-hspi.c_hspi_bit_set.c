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
struct hspi_priv {int dummy; } ;

/* Variables and functions */
 int hspi_read (struct hspi_priv*,int) ; 
 int /*<<< orphan*/  hspi_write (struct hspi_priv*,int,int) ; 

__attribute__((used)) static void hspi_bit_set(struct hspi_priv *hspi, int reg, u32 mask, u32 set)
{
	u32 val = hspi_read(hspi, reg);

	val &= ~mask;
	val |= set & mask;

	hspi_write(hspi, reg, val);
}