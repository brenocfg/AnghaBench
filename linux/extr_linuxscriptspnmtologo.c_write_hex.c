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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  out ; 
 int write_hex_cnt ; 

__attribute__((used)) static void write_hex(unsigned char byte)
{
    if (write_hex_cnt % 12)
	fprintf(out, ", 0x%02x", byte);
    else if (write_hex_cnt)
	fprintf(out, ",\n\t0x%02x", byte);
    else
	fprintf(out, "\t0x%02x", byte);
    write_hex_cnt++;
}