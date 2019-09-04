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
struct buffer_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_LNE_define_file ; 
 int /*<<< orphan*/  buffer_ext_add (struct buffer_ext*,void*,int) ; 
 int /*<<< orphan*/  emit_opcode (struct buffer_ext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_string (struct buffer_ext*,char const*) ; 
 int /*<<< orphan*/  emit_unsigned_LEB128 (struct buffer_ext*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void emit_lne_define_filename(struct buffer_ext *be,
				     const char *filename)
{
	buffer_ext_add(be, (void *)"", 1);

	/* LNE field, strlen(filename) + zero termination, 3 bytes for: the dir entry, timestamp, filesize */
	emit_unsigned_LEB128(be, strlen(filename) + 5);
	emit_opcode(be, DW_LNE_define_file);
	emit_string(be, filename);
	/* directory index 0=do not know */
        emit_unsigned_LEB128(be, 0);
	/* last modification date on file 0=do not know */
        emit_unsigned_LEB128(be, 0);
	/* filesize 0=do not know */
        emit_unsigned_LEB128(be, 0);
}