#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int remaining_chars; char* sz_data; } ;
struct TYPE_9__ {TYPE_3__ chars8; } ;
struct TYPE_10__ {TYPE_4__ cu; } ;
struct hpi_response {TYPE_5__ u; scalar_t__ error; } ;
struct TYPE_6__ {unsigned int param1; scalar_t__ param2; scalar_t__ attribute; } ;
struct TYPE_7__ {TYPE_1__ c; } ;
struct hpi_message {TYPE_2__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_CONTROL_GET_STATE ; 
 scalar_t__ HPI_ERROR_INVALID_CONTROL_VALUE ; 
 scalar_t__ HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 scalar_t__ hpi_handle_indexes (int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static u16 hpi_control_get_string(const u32 h_control, const u16 attribute,
	char *psz_string, const u32 string_length)
{
	unsigned int sub_string_index = 0, j = 0;
	char c = 0;
	unsigned int n = 0;
	u16 err = 0;

	if ((string_length < 1) || (string_length > 256))
		return HPI_ERROR_INVALID_CONTROL_VALUE;
	for (sub_string_index = 0; sub_string_index < string_length;
		sub_string_index += 8) {
		struct hpi_message hm;
		struct hpi_response hr;

		hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
			HPI_CONTROL_GET_STATE);
		if (hpi_handle_indexes(h_control, &hm.adapter_index,
				&hm.obj_index))
			return HPI_ERROR_INVALID_HANDLE;
		hm.u.c.attribute = attribute;
		hm.u.c.param1 = sub_string_index;
		hm.u.c.param2 = 0;
		hpi_send_recv(&hm, &hr);

		if (sub_string_index == 0
			&& (hr.u.cu.chars8.remaining_chars + 8) >
			string_length)
			return HPI_ERROR_INVALID_CONTROL_VALUE;

		if (hr.error) {
			err = hr.error;
			break;
		}
		for (j = 0; j < 8; j++) {
			c = hr.u.cu.chars8.sz_data[j];
			psz_string[sub_string_index + j] = c;
			n++;
			if (n >= string_length) {
				psz_string[string_length - 1] = 0;
				err = HPI_ERROR_INVALID_CONTROL_VALUE;
				break;
			}
			if (c == 0)
				break;
		}

		if ((hr.u.cu.chars8.remaining_chars == 0)
			&& ((sub_string_index + j) < string_length)
			&& (c != 0)) {
			c = 0;
			psz_string[sub_string_index + j] = c;
		}
		if (c == 0)
			break;
	}
	return err;
}