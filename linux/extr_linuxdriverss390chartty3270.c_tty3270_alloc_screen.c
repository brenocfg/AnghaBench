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
struct tty3270_line {struct tty3270_line* cells; } ;
struct tty3270_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tty3270_line* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tty3270_line*) ; 
 void* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tty3270_line *
tty3270_alloc_screen(unsigned int rows, unsigned int cols)
{
	struct tty3270_line *screen;
	unsigned long size;
	int lines;

	size = sizeof(struct tty3270_line) * (rows - 2);
	screen = kzalloc(size, GFP_KERNEL);
	if (!screen)
		goto out_err;
	for (lines = 0; lines < rows - 2; lines++) {
		size = sizeof(struct tty3270_cell) * cols;
		screen[lines].cells = kzalloc(size, GFP_KERNEL);
		if (!screen[lines].cells)
			goto out_screen;
	}
	return screen;
out_screen:
	while (lines--)
		kfree(screen[lines].cells);
	kfree(screen);
out_err:
	return ERR_PTR(-ENOMEM);
}