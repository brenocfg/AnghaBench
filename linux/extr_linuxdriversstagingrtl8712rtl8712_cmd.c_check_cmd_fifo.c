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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 

__attribute__((used)) static u8 check_cmd_fifo(struct _adapter *padapter, uint sz)
{
	return _SUCCESS;
}