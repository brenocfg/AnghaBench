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
 char TTY_NORMAL ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  n_tty_receive_char_closing (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
n_tty_receive_buf_closing(struct tty_struct *tty, const unsigned char *cp,
			  char *fp, int count)
{
	char flag = TTY_NORMAL;

	while (count--) {
		if (fp)
			flag = *fp++;
		if (likely(flag == TTY_NORMAL))
			n_tty_receive_char_closing(tty, *cp++);
	}
}