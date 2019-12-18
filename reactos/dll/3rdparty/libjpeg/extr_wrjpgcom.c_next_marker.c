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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int read_1_byte () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
next_marker (void)
{
  int c;
  int discarded_bytes = 0;

  /* Find 0xFF byte; count and skip any non-FFs. */
  c = read_1_byte();
  while (c != 0xFF) {
    discarded_bytes++;
    c = read_1_byte();
  }
  /* Get marker code byte, swallowing any duplicate FF bytes.  Extra FFs
   * are legal as pad bytes, so don't count them in discarded_bytes.
   */
  do {
    c = read_1_byte();
  } while (c == 0xFF);

  if (discarded_bytes != 0) {
    fprintf(stderr, "Warning: garbage data found in JPEG file\n");
  }

  return c;
}