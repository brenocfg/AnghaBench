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
typedef  int cell_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int) ; 

__attribute__((used)) static void asm_emit_cell(void *e, cell_t val)
{
	FILE *f = e;

	fprintf(f, "\t.byte 0x%02x; .byte 0x%02x; .byte 0x%02x; .byte 0x%02x\n",
		(val >> 24) & 0xff, (val >> 16) & 0xff,
		(val >> 8) & 0xff, val & 0xff);
}