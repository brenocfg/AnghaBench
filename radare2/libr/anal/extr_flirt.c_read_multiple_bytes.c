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
typedef  int ut32 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int read_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ read_short (int /*<<< orphan*/ *) ; 
 int read_word (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut32 read_multiple_bytes(RBuffer *b) {
	ut32 r = read_byte (b);
	if ((r & 0x80) != 0x80) {
		return r;
	}
	if ((r & 0xc0) != 0xc0) {
		return ((r & 0x7f) << 8) + read_byte (b);
	}
	if ((r & 0xe0) != 0xe0) {
		r = ((r & 0x3f) << 24) + (read_byte (b) << 16);
		r += read_short (b);
		return r;
	}
	return read_word (b);
}