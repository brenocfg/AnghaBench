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
struct _adapter {int dummy; } ;

/* Variables and functions */
 int efuse_available_max_size ; 

int r8712_efuse_get_max_size(struct _adapter *padapter)
{
	return	efuse_available_max_size;
}