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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int n_tty_receive_buf_common (struct tty_struct*,unsigned char const*,char*,int,int) ; 

__attribute__((used)) static int n_tty_receive_buf2(struct tty_struct *tty, const unsigned char *cp,
			      char *fp, int count)
{
	return n_tty_receive_buf_common(tty, cp, fp, count, 1);
}