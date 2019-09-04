#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bit_values; } ;
struct TYPE_5__ {TYPE_1__ bit_values; int /*<<< orphan*/  cdw_params; int /*<<< orphan*/  cdw_locals; int /*<<< orphan*/  cb_proc_size; int /*<<< orphan*/  ul_off_start; } ;
typedef  TYPE_2__ SFPO_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  READ2 (int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP_UINT16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut16 ; 
 int /*<<< orphan*/  ut32 ; 

__attribute__((used)) static int parse_fpo_data(char *data, int data_size, int *read_bytes, SFPO_DATA *fpo_data)
{
	int curr_read_bytes = *read_bytes;

	READ4(*read_bytes, data_size, fpo_data->ul_off_start, data, ut32);
	READ4(*read_bytes, data_size, fpo_data->cb_proc_size, data, ut32);
	READ4(*read_bytes, data_size, fpo_data->cdw_locals, data, ut32);
	READ2(*read_bytes, data_size, fpo_data->cdw_params, data, ut16);
	READ2(*read_bytes, data_size, fpo_data->bit_values.bit_values, data, ut16);

	fpo_data->bit_values.bit_values = SWAP_UINT16(fpo_data->bit_values.bit_values);

	return (*read_bytes - curr_read_bytes);
}