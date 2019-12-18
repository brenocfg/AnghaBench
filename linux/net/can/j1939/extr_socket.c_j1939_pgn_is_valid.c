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
typedef  scalar_t__ pgn_t ;

/* Variables and functions */
 scalar_t__ J1939_PGN_MAX ; 

__attribute__((used)) static inline bool j1939_pgn_is_valid(pgn_t pgn)
{
	return pgn <= J1939_PGN_MAX;
}