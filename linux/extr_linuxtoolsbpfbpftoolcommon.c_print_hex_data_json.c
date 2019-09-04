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
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 

void print_hex_data_json(uint8_t *data, size_t len)
{
	unsigned int i;

	jsonw_start_array(json_wtr);
	for (i = 0; i < len; i++)
		jsonw_printf(json_wtr, "\"0x%02hhx\"", data[i]);
	jsonw_end_array(json_wtr);
}