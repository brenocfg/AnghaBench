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
typedef  int u8 ;
typedef  int u32 ;
struct da9150_fg {int /*<<< orphan*/  da9150; } ;

/* Variables and functions */
 int DA9150_QIF_BYTE_SIZE ; 
 int DA9150_QIF_CODE_MASK ; 
 int DA9150_QIF_LONG_SIZE ; 
 int DA9150_QIF_READ ; 
 int /*<<< orphan*/  da9150_read_qif (int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static u32 da9150_fg_read_attr(struct da9150_fg *fg, u8 code, u8 size)

{
	u8 buf[DA9150_QIF_LONG_SIZE];
	u8 read_addr;
	u32 res = 0;
	int i;

	/* Set QIF code (READ mode) */
	read_addr = (code & DA9150_QIF_CODE_MASK) | DA9150_QIF_READ;

	da9150_read_qif(fg->da9150, read_addr, size, buf);
	for (i = 0; i < size; ++i)
		res |= (buf[i] << (i * DA9150_QIF_BYTE_SIZE));

	return res;
}