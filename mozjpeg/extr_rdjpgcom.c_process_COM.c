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

/* Variables and functions */
 int /*<<< orphan*/  ERREXIT (char*) ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ ) ; 
 int read_1_byte () ; 
 unsigned int read_2_bytes () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
process_COM(int raw)
{
  unsigned int length;
  int ch;
  int lastch = 0;

  /* Bill Allombert: set locale properly for isprint */
#ifdef HAVE_LOCALE_H
  setlocale(LC_CTYPE, "");
#endif

  /* Get the marker parameter length count */
  length = read_2_bytes();
  /* Length includes itself, so must be at least 2 */
  if (length < 2)
    ERREXIT("Erroneous JPEG marker length");
  length -= 2;

  while (length > 0) {
    ch = read_1_byte();
    if (raw) {
      putc(ch, stdout);
    /* Emit the character in a readable form.
     * Nonprintables are converted to \nnn form,
     * while \ is converted to \\.
     * Newlines in CR, CR/LF, or LF form will be printed as one newline.
     */
    } else if (ch == '\r') {
      printf("\n");
    } else if (ch == '\n') {
      if (lastch != '\r')
        printf("\n");
    } else if (ch == '\\') {
      printf("\\\\");
    } else if (isprint(ch)) {
      putc(ch, stdout);
    } else {
      printf("\\%03o", ch);
    }
    lastch = ch;
    length--;
  }
  printf("\n");

  /* Bill Allombert: revert to C locale */
#ifdef HAVE_LOCALE_H
  setlocale(LC_CTYPE, "C");
#endif
}