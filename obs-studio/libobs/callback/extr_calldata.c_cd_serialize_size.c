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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline size_t cd_serialize_size(uint8_t **pos)
{
	size_t size = 0;
	memcpy(&size, *pos, sizeof(size_t));
	*pos += sizeof(size_t);
	return size;
}