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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  TX_CS (int) ; 
 int TX_CS_SNG_STATE ; 
 int nr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_tx_cs_sng_poll(struct niu *np, int channel)
{
	int limit = 1000;

	while (--limit > 0) {
		u64 val = nr64(TX_CS(channel));
		if (val & TX_CS_SNG_STATE)
			return 0;
	}
	return -ENODEV;
}