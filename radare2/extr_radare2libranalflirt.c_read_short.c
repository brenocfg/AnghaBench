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
typedef  int ut16 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int read_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut16 read_short(RBuffer *b) {
	ut16 r = (read_byte (b) << 8);
	r += read_byte (b);
	return r;
}