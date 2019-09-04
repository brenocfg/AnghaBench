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
 int /*<<< orphan*/  FIFO_DATA_LOW ; 
 int /*<<< orphan*/  nsp32_multi_write4 (unsigned int,int /*<<< orphan*/ ,void*,unsigned long) ; 

__attribute__((used)) static inline void nsp32_fifo_write(unsigned int   base,
				    void          *buf,
				    unsigned long  count)
{
	nsp32_multi_write4(base, FIFO_DATA_LOW, buf, count);
}