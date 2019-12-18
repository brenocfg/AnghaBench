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
typedef  enum printFormat { ____Placeholder_printFormat } printFormat ;

/* Variables and functions */
#define  PRINT_ALIGNED 137 
#define  PRINT_ASCIIDOC 136 
#define  PRINT_CSV 135 
#define  PRINT_HTML 134 
#define  PRINT_LATEX 133 
#define  PRINT_LATEX_LONGTABLE 132 
#define  PRINT_NOTHING 131 
#define  PRINT_TROFF_MS 130 
#define  PRINT_UNALIGNED 129 
#define  PRINT_WRAPPED 128 

__attribute__((used)) static const char *
_align2string(enum printFormat in)
{
	switch (in)
	{
		case PRINT_NOTHING:
			return "nothing";
			break;
		case PRINT_ALIGNED:
			return "aligned";
			break;
		case PRINT_ASCIIDOC:
			return "asciidoc";
			break;
		case PRINT_CSV:
			return "csv";
			break;
		case PRINT_HTML:
			return "html";
			break;
		case PRINT_LATEX:
			return "latex";
			break;
		case PRINT_LATEX_LONGTABLE:
			return "latex-longtable";
			break;
		case PRINT_TROFF_MS:
			return "troff-ms";
			break;
		case PRINT_UNALIGNED:
			return "unaligned";
			break;
		case PRINT_WRAPPED:
			return "wrapped";
			break;
	}
	return "unknown";
}