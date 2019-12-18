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
typedef  int /*<<< orphan*/  SOmapEntry ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int parse_omap_entry(char *data, int data_size, int *read_bytes, SOmapEntry *omap_entry) {
	int curr_read_bytes = *read_bytes;
	memcpy (omap_entry, data, sizeof (SOmapEntry));
	*read_bytes += sizeof (SOmapEntry);
	return (*read_bytes - curr_read_bytes);
}