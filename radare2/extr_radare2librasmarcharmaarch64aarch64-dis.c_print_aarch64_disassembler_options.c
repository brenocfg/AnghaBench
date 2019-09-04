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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
print_aarch64_disassembler_options (FILE *stream)
{
  fprintf (stream, _("\n\
The following AARCH64 specific disassembler options are supported for use\n\
with the -M switch (multiple options should be separated by commas):\n"));

  fprintf (stream, _("\n\
  no-aliases         Don't print instruction aliases.\n"));

  fprintf (stream, _("\n\
  aliases            Do print instruction aliases.\n"));

  fprintf (stream, _("\n\
  no-notes         Don't print instruction notes.\n"));

  fprintf (stream, _("\n\
  notes            Do print instruction notes.\n"));

#ifdef DEBUG_AARCH64
  fprintf (stream, _("\n\
  debug_dump         Temp switch for debug trace.\n"));
#endif /* DEBUG_AARCH64 */

  fprintf (stream, _("\n"));
}