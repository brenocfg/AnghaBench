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
typedef  int pgn_t ;

/* Variables and functions */
 scalar_t__ j1939_pgn_is_pdu1 (int) ; 

__attribute__((used)) static inline bool j1939_pgn_is_clean_pdu(pgn_t pgn)
{
	if (j1939_pgn_is_pdu1(pgn))
		return !(pgn & 0xff);
	else
		return true;
}