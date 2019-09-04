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

/* Variables and functions */
 scalar_t__ TB_PROPERTY_KEY_SIZE ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static bool tb_property_key_valid(const char *key)
{
	return key && strlen(key) <= TB_PROPERTY_KEY_SIZE;
}