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
typedef  int /*<<< orphan*/  pcre2_output_context ;
typedef  int /*<<< orphan*/  PCRE2_UCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_BACKSLASH ; 
 int /*<<< orphan*/  convert_glob_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
convert_glob_print_separator(pcre2_output_context *out,
  PCRE2_UCHAR separator, BOOL with_escape)
{
if (with_escape)
  convert_glob_write(out, CHAR_BACKSLASH);

convert_glob_write(out, separator);
}