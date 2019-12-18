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
struct printer_data {int hit_nul; int is_printable; int /*<<< orphan*/  line_no; } ;
typedef  enum binary_printer_ops { ____Placeholder_binary_printer_ops } binary_printer_ops ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  BINARY_PRINT_ADDR 137 
#define  BINARY_PRINT_CHAR_DATA 136 
#define  BINARY_PRINT_CHAR_PAD 135 
#define  BINARY_PRINT_DATA_BEGIN 134 
#define  BINARY_PRINT_DATA_END 133 
#define  BINARY_PRINT_LINE_BEGIN 132 
#define  BINARY_PRINT_LINE_END 131 
#define  BINARY_PRINT_NUM_DATA 130 
#define  BINARY_PRINT_NUM_PAD 129 
#define  BINARY_PRINT_SEP 128 
 int fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 

__attribute__((used)) static int sample__fprintf_bpf_output(enum binary_printer_ops op,
				      unsigned int val,
				      void *extra, FILE *fp)
{
	unsigned char ch = (unsigned char)val;
	struct printer_data *printer_data = extra;
	int printed = 0;

	switch (op) {
	case BINARY_PRINT_DATA_BEGIN:
		printed += fprintf(fp, "\n");
		break;
	case BINARY_PRINT_LINE_BEGIN:
		printed += fprintf(fp, "%17s", !printer_data->line_no ? "BPF output:" :
						        "           ");
		break;
	case BINARY_PRINT_ADDR:
		printed += fprintf(fp, " %04x:", val);
		break;
	case BINARY_PRINT_NUM_DATA:
		printed += fprintf(fp, " %02x", val);
		break;
	case BINARY_PRINT_NUM_PAD:
		printed += fprintf(fp, "   ");
		break;
	case BINARY_PRINT_SEP:
		printed += fprintf(fp, "  ");
		break;
	case BINARY_PRINT_CHAR_DATA:
		if (printer_data->hit_nul && ch)
			printer_data->is_printable = false;

		if (!isprint(ch)) {
			printed += fprintf(fp, "%c", '.');

			if (!printer_data->is_printable)
				break;

			if (ch == '\0')
				printer_data->hit_nul = true;
			else
				printer_data->is_printable = false;
		} else {
			printed += fprintf(fp, "%c", ch);
		}
		break;
	case BINARY_PRINT_CHAR_PAD:
		printed += fprintf(fp, " ");
		break;
	case BINARY_PRINT_LINE_END:
		printed += fprintf(fp, "\n");
		printer_data->line_no++;
		break;
	case BINARY_PRINT_DATA_END:
	default:
		break;
	}

	return printed;
}