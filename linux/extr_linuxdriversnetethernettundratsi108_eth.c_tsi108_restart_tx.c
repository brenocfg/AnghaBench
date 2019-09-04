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
struct tsi108_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSI108_EC_TXCTRL ; 
 int TSI108_EC_TXCTRL_GO ; 
 int TSI108_EC_TXCTRL_IDLEINT ; 
 int TSI108_EC_TXCTRL_QUEUE0 ; 
 int /*<<< orphan*/  TSI108_EC_TXQ_PTRHIGH ; 
 int TSI108_EC_TXQ_PTRHIGH_VALID ; 
 int /*<<< orphan*/  TSI_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tsi108_restart_tx(struct tsi108_prv_data * data)
{
	TSI_WRITE(TSI108_EC_TXQ_PTRHIGH,
			     TSI108_EC_TXQ_PTRHIGH_VALID);

	TSI_WRITE(TSI108_EC_TXCTRL, TSI108_EC_TXCTRL_IDLEINT |
			     TSI108_EC_TXCTRL_GO | TSI108_EC_TXCTRL_QUEUE0);
}