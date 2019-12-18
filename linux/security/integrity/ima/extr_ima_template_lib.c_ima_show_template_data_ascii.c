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
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct ima_field_data {int len; int /*<<< orphan*/ * data; } ;
typedef  enum ima_show_type { ____Placeholder_ima_show_type } ima_show_type ;
typedef  enum data_formats { ____Placeholder_data_formats } data_formats ;

/* Variables and functions */
#define  DATA_FMT_DIGEST 131 
#define  DATA_FMT_DIGEST_WITH_ALGO 130 
#define  DATA_FMT_HEX 129 
#define  DATA_FMT_STRING 128 
 int /*<<< orphan*/  ima_print_digest (struct seq_file*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strnchr (int /*<<< orphan*/ *,int,char) ; 

__attribute__((used)) static void ima_show_template_data_ascii(struct seq_file *m,
					 enum ima_show_type show,
					 enum data_formats datafmt,
					 struct ima_field_data *field_data)
{
	u8 *buf_ptr = field_data->data;
	u32 buflen = field_data->len;

	switch (datafmt) {
	case DATA_FMT_DIGEST_WITH_ALGO:
		buf_ptr = strnchr(field_data->data, buflen, ':');
		if (buf_ptr != field_data->data)
			seq_printf(m, "%s", field_data->data);

		/* skip ':' and '\0' */
		buf_ptr += 2;
		buflen -= buf_ptr - field_data->data;
		/* fall through */
	case DATA_FMT_DIGEST:
	case DATA_FMT_HEX:
		if (!buflen)
			break;
		ima_print_digest(m, buf_ptr, buflen);
		break;
	case DATA_FMT_STRING:
		seq_printf(m, "%s", buf_ptr);
		break;
	default:
		break;
	}
}