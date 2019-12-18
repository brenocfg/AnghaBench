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
 int DEFAULT_XLOG_SEG_SIZE ; 
 scalar_t__ TYPEALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLOG_BLCKSZ ; 
 char* buf ; 
 int /*<<< orphan*/ * full_buf ; 
 int /*<<< orphan*/  random () ; 

__attribute__((used)) static void
prepare_buf(void)
{
	int			ops;

	/* write random data into buffer */
	for (ops = 0; ops < DEFAULT_XLOG_SEG_SIZE; ops++)
		full_buf[ops] = random();

	buf = (char *) TYPEALIGN(XLOG_BLCKSZ, full_buf);
}