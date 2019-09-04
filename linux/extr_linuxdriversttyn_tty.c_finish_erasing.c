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
struct n_tty_data {scalar_t__ erasing; } ;

/* Variables and functions */
 int /*<<< orphan*/  echo_char_raw (char,struct n_tty_data*) ; 

__attribute__((used)) static inline void finish_erasing(struct n_tty_data *ldata)
{
	if (ldata->erasing) {
		echo_char_raw('/', ldata);
		ldata->erasing = 0;
	}
}