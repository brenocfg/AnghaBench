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
typedef  int /*<<< orphan*/  SFPO_DATA_V2 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int parse_fpo_data_v2(char *data, int data_size, int *read_bytes, SFPO_DATA_V2 *fpo_data)
{
	int curr_read_bytes = *read_bytes;

	memcpy(fpo_data, data, sizeof(SFPO_DATA_V2));
	*read_bytes += sizeof(SFPO_DATA_V2);

	return (*read_bytes - curr_read_bytes);
}