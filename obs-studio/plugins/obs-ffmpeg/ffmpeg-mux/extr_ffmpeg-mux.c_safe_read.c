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
 size_t fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static size_t safe_read(void *vdata, size_t size)
{
	uint8_t *data = vdata;
	size_t total = size;

	while (size > 0) {
		size_t in_size = fread(data, 1, size, stdin);
		if (in_size == 0)
			return 0;

		size -= in_size;
		data += in_size;
	}

	return total;
}