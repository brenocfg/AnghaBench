#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ lineno; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ source_file ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int LINE_BUF_SIZE ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int remove_newlines (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_lines(source_file *file, uint16_t line_min, uint16_t line_max)
{
  char buf[LINE_BUF_SIZE];
  int show_lineno = 1, found_newline = 0, is_printed = 0;

  if (file->fp == NULL) {
    return;
  }

  while (fgets(buf, sizeof(buf), file->fp) != NULL) {
    found_newline = remove_newlines(buf, file->fp);

    if (line_min <= file->lineno) {
      if (show_lineno) {
        printf("%-8d", file->lineno);
      }
      show_lineno = found_newline;
      printf(found_newline ? "%s\n" : "%s", buf);
      is_printed = 1;
    }

    if (found_newline) {
      if (line_max < ++file->lineno) {
        break;
      }
    }
  }

  if (is_printed && !found_newline) {
    printf("\n");
  }
}