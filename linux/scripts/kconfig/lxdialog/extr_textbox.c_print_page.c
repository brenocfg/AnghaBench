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
typedef  int /*<<< orphan*/  (* update_text_fn ) (int,char*,char*,void*) ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  back_lines (int) ; 
 int buf ; 
 scalar_t__ end_reached ; 
 int /*<<< orphan*/  get_line () ; 
 char* page ; 
 scalar_t__ page_length ; 
 int /*<<< orphan*/  print_line (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_page(WINDOW *win, int height, int width, update_text_fn
		       update_text, void *data)
{
	int i, passed_end = 0;

	if (update_text) {
		char *end;

		for (i = 0; i < height; i++)
			get_line();
		end = page;
		back_lines(height);
		update_text(buf, page - buf, end - buf, data);
	}

	page_length = 0;
	for (i = 0; i < height; i++) {
		print_line(win, i, width);
		if (!passed_end)
			page_length++;
		if (end_reached && !passed_end)
			passed_end = 1;
	}
	wnoutrefresh(win);
}