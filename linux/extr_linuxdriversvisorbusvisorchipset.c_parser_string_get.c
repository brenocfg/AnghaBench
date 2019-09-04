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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int strnlen (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *parser_string_get(u8 *pscan, int nscan)
{
	int value_length;
	void *value;

	if (nscan == 0)
		return NULL;

	value_length = strnlen(pscan, nscan);
	value = kzalloc(value_length + 1, GFP_KERNEL);
	if (!value)
		return NULL;
	if (value_length > 0)
		memcpy(value, pscan, value_length);
	return value;
}