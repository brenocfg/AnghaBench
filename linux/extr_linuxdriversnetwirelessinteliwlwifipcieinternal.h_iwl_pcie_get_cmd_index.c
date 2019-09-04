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
typedef  int u16 ;
struct iwl_txq {int n_window; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 iwl_pcie_get_cmd_index(const struct iwl_txq *q, u32 index)
{
	return index & (q->n_window - 1);
}