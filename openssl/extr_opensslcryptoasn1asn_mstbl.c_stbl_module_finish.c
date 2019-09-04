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
typedef  int /*<<< orphan*/  CONF_IMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_TABLE_cleanup () ; 

__attribute__((used)) static void stbl_module_finish(CONF_IMODULE *md)
{
    ASN1_STRING_TABLE_cleanup();
}