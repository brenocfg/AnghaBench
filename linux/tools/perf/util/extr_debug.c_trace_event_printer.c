#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
union perf_event {TYPE_1__ header; } ;
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
 char* PERF_COLOR_BLUE ; 
 int color_fprintf (int /*<<< orphan*/ *,char const*,char*,...) ; 
 int fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 

__attribute__((used)) static int trace_event_printer(enum binary_printer_ops op,
			       unsigned int val, void *extra, FILE *fp)
{
	const char *color = PERF_COLOR_BLUE;
	union perf_event *event = (union perf_event *)extra;
	unsigned char ch = (unsigned char)val;
	int printed = 0;

	switch (op) {
	case BINARY_PRINT_DATA_BEGIN:
		printed += fprintf(fp, ".");
		printed += color_fprintf(fp, color, "\n. ... raw event: size %d bytes\n",
					 event->header.size);
		break;
	case BINARY_PRINT_LINE_BEGIN:
		printed += fprintf(fp, ".");
		break;
	case BINARY_PRINT_ADDR:
		printed += color_fprintf(fp, color, "  %04x: ", val);
		break;
	case BINARY_PRINT_NUM_DATA:
		printed += color_fprintf(fp, color, " %02x", val);
		break;
	case BINARY_PRINT_NUM_PAD:
		printed += color_fprintf(fp, color, "   ");
		break;
	case BINARY_PRINT_SEP:
		printed += color_fprintf(fp, color, "  ");
		break;
	case BINARY_PRINT_CHAR_DATA:
		printed += color_fprintf(fp, color, "%c",
			      isprint(ch) ? ch : '.');
		break;
	case BINARY_PRINT_CHAR_PAD:
		printed += color_fprintf(fp, color, " ");
		break;
	case BINARY_PRINT_LINE_END:
		printed += color_fprintf(fp, color, "\n");
		break;
	case BINARY_PRINT_DATA_END:
		printed += fprintf(fp, "\n");
		break;
	default:
		break;
	}

	return printed;
}