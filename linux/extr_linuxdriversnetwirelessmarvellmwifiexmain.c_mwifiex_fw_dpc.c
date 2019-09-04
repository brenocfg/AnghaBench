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
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mwifiex_fw_dpc (struct firmware const*,void*) ; 

__attribute__((used)) static void mwifiex_fw_dpc(const struct firmware *firmware, void *context)
{
	_mwifiex_fw_dpc(firmware, context);
}