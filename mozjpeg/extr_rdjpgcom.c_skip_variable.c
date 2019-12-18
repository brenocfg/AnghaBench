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
 int /*<<< orphan*/  read_1_byte () ; 
 unsigned int read_2_bytes () ; 

__attribute__((used)) static void
skip_variable(void)
/* Skip over an unknown or uninteresting variable-length marker */
{
  unsigned int length;

  /* Get the marker parameter length count */
  length = read_2_bytes();
  /* Length includes itself, so must be at least 2 */
  if (length < 2)
    ERREXIT("Erroneous JPEG marker length");
  length -= 2;
  /* Skip over the remaining bytes */
  while (length > 0) {
    (void)read_1_byte();
    length--;
  }
}