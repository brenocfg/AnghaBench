#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * out_str; } ;
typedef  TYPE_1__ pcre2_output_context ;
typedef  int /*<<< orphan*/  PCRE2_UCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_CIRCUMFLEX_ACCENT ; 
 int /*<<< orphan*/  CHAR_LEFT_SQUARE_BRACKET ; 
 int /*<<< orphan*/  CHAR_RIGHT_SQUARE_BRACKET ; 
 int /*<<< orphan*/  convert_glob_print_separator (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_glob_write (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_glob_write_str (TYPE_1__*,int) ; 

__attribute__((used)) static void
convert_glob_print_wildcard(pcre2_output_context *out,
  PCRE2_UCHAR separator, BOOL with_escape)
{
out->out_str[0] = CHAR_LEFT_SQUARE_BRACKET;
out->out_str[1] = CHAR_CIRCUMFLEX_ACCENT;
convert_glob_write_str(out, 2);

convert_glob_print_separator(out, separator, with_escape);

convert_glob_write(out, CHAR_RIGHT_SQUARE_BRACKET);
}