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
typedef  int /*<<< orphan*/  SPIPlanPtr ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_prepare_cursor (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SPIPlanPtr
SPI_prepare(const char *src, int nargs, Oid *argtypes)
{
	return SPI_prepare_cursor(src, nargs, argtypes, 0);
}