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
 int /*<<< orphan*/  put_unaligned_be32 (int,unsigned char*) ; 

__attribute__((used)) static void int_to_threadref(unsigned char *id, int value)
{
	put_unaligned_be32(value, id);
}