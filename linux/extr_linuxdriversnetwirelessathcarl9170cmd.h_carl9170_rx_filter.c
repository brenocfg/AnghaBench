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
struct ar9170 {int dummy; } ;
typedef  int /*<<< orphan*/  rx_filter ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_RX_FILTER ; 
 int carl9170_exec_cmd (struct ar9170*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int const) ; 

__attribute__((used)) static inline int carl9170_rx_filter(struct ar9170 *ar,
				     const unsigned int _rx_filter)
{
	__le32 rx_filter = cpu_to_le32(_rx_filter);

	return carl9170_exec_cmd(ar, CARL9170_CMD_RX_FILTER,
				sizeof(rx_filter), (u8 *)&rx_filter,
				0, NULL);
}