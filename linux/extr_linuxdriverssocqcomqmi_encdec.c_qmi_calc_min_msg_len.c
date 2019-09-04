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
typedef  int /*<<< orphan*/  u16 ;
struct qmi_elem_info {scalar_t__ data_type; int elem_size; int elem_len; struct qmi_elem_info* ei_array; } ;

/* Variables and functions */
 scalar_t__ QMI_DATA_LEN ; 
 scalar_t__ QMI_EOTI ; 
 scalar_t__ QMI_OPT_FLAG ; 
 scalar_t__ QMI_STRING ; 
 scalar_t__ QMI_STRUCT ; 
 scalar_t__ TLV_LEN_SIZE ; 
 scalar_t__ TLV_TYPE_SIZE ; 
 int U8_MAX ; 
 struct qmi_elem_info* skip_to_next_elem (struct qmi_elem_info*,int) ; 

__attribute__((used)) static int qmi_calc_min_msg_len(struct qmi_elem_info *ei_array,
				int level)
{
	int min_msg_len = 0;
	struct qmi_elem_info *temp_ei = ei_array;

	if (!ei_array)
		return min_msg_len;

	while (temp_ei->data_type != QMI_EOTI) {
		/* Optional elements do not count in minimum length */
		if (temp_ei->data_type == QMI_OPT_FLAG) {
			temp_ei = skip_to_next_elem(temp_ei, level);
			continue;
		}

		if (temp_ei->data_type == QMI_DATA_LEN) {
			min_msg_len += (temp_ei->elem_size == sizeof(u8) ?
					sizeof(u8) : sizeof(u16));
			temp_ei++;
			continue;
		} else if (temp_ei->data_type == QMI_STRUCT) {
			min_msg_len += qmi_calc_min_msg_len(temp_ei->ei_array,
							    (level + 1));
			temp_ei++;
		} else if (temp_ei->data_type == QMI_STRING) {
			if (level > 1)
				min_msg_len += temp_ei->elem_len <= U8_MAX ?
					sizeof(u8) : sizeof(u16);
			min_msg_len += temp_ei->elem_len * temp_ei->elem_size;
			temp_ei++;
		} else {
			min_msg_len += (temp_ei->elem_len * temp_ei->elem_size);
			temp_ei++;
		}

		/*
		 * Type & Length info. not prepended for elements in the
		 * nested structure.
		 */
		if (level == 1)
			min_msg_len += (TLV_TYPE_SIZE + TLV_LEN_SIZE);
	}

	return min_msg_len;
}