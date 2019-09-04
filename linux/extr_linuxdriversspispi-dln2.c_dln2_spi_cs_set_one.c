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
typedef  int /*<<< orphan*/  u8 ;
struct dln2_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int dln2_spi_cs_set (struct dln2_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_spi_cs_set_one(struct dln2_spi *dln2, u8 cs)
{
	return dln2_spi_cs_set(dln2, BIT(cs));
}