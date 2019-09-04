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
struct seq_file {int dummy; } ;
struct ima_field_data {int dummy; } ;
typedef  enum ima_show_type { ____Placeholder_ima_show_type } ima_show_type ;
typedef  enum data_formats { ____Placeholder_data_formats } data_formats ;

/* Variables and functions */
#define  IMA_SHOW_ASCII 131 
#define  IMA_SHOW_BINARY 130 
#define  IMA_SHOW_BINARY_NO_FIELD_LEN 129 
#define  IMA_SHOW_BINARY_OLD_STRING_FMT 128 
 int /*<<< orphan*/  ima_show_template_data_ascii (struct seq_file*,int,int,struct ima_field_data*) ; 
 int /*<<< orphan*/  ima_show_template_data_binary (struct seq_file*,int,int,struct ima_field_data*) ; 

__attribute__((used)) static void ima_show_template_field_data(struct seq_file *m,
					 enum ima_show_type show,
					 enum data_formats datafmt,
					 struct ima_field_data *field_data)
{
	switch (show) {
	case IMA_SHOW_ASCII:
		ima_show_template_data_ascii(m, show, datafmt, field_data);
		break;
	case IMA_SHOW_BINARY:
	case IMA_SHOW_BINARY_NO_FIELD_LEN:
	case IMA_SHOW_BINARY_OLD_STRING_FMT:
		ima_show_template_data_binary(m, show, datafmt, field_data);
		break;
	default:
		break;
	}
}