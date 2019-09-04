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
struct n_tty_data {int /*<<< orphan*/  read_head; } ;

/* Variables and functions */
 unsigned char* read_buf_addr (struct n_tty_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void put_tty_queue(unsigned char c, struct n_tty_data *ldata)
{
	*read_buf_addr(ldata, ldata->read_head) = c;
	ldata->read_head++;
}