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
 int ESCDELAY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KEY_F (int) ; 
 size_t MAIN_MENU_BACK ; 
 size_t MAIN_MENU_FORE ; 
 size_t MAIN_MENU_GREY ; 
 int /*<<< orphan*/  O_IGNORECASE ; 
 int /*<<< orphan*/  O_NONCYCLIC ; 
 int /*<<< orphan*/  O_ONEVALUE ; 
 int /*<<< orphan*/  O_SHOWDESC ; 
 int /*<<< orphan*/  O_SHOWMATCH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * attributes ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  clear () ; 
 int /*<<< orphan*/  conf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_get_configname () ; 
 int /*<<< orphan*/ * conf_message_callback ; 
 int /*<<< orphan*/  conf_parse (char*) ; 
 int /*<<< orphan*/  conf_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conf_set_message_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curses_menu ; 
 int /*<<< orphan*/  curses_menu_items ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ ) ; 
 scalar_t__ do_exit () ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  free_menu (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  global_exit ; 
 scalar_t__ has_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_window ; 
 int /*<<< orphan*/  menu_no_f_instructions ; 
 int /*<<< orphan*/  menu_opts_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_opts_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  notimeout (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  set_colors () ; 
 int /*<<< orphan*/  set_config_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_escdelay (int) ; 
 int /*<<< orphan*/  set_menu_back (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_menu_fore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_menu_grey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_menu_mark (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setup_windows () ; 
 int /*<<< orphan*/  show_scroll_win (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int single_menu_mode ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  unpost_menu (int /*<<< orphan*/ ) ; 

int main(int ac, char **av)
{
	int lines, columns;
	char *mode;

	if (ac > 1 && strcmp(av[1], "-s") == 0) {
		/* Silence conf_read() until the real callback is set up */
		conf_set_message_callback(NULL);
		av++;
	}
	conf_parse(av[1]);
	conf_read(NULL);

	mode = getenv("NCONFIG_MODE");
	if (mode) {
		if (!strcasecmp(mode, "single_menu"))
			single_menu_mode = 1;
	}

	/* Initialize curses */
	initscr();
	/* set color theme */
	set_colors();

	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	getmaxyx(stdscr, lines, columns);
	if (columns < 75 || lines < 20) {
		endwin();
		printf("Your terminal should have at "
			"least 20 lines and 75 columns\n");
		return 1;
	}

	notimeout(stdscr, FALSE);
#if NCURSES_REENTRANT
	set_escdelay(1);
#else
	ESCDELAY = 1;
#endif

	/* set btns menu */
	curses_menu = new_menu(curses_menu_items);
	menu_opts_off(curses_menu, O_SHOWDESC);
	menu_opts_on(curses_menu, O_SHOWMATCH);
	menu_opts_on(curses_menu, O_ONEVALUE);
	menu_opts_on(curses_menu, O_NONCYCLIC);
	menu_opts_on(curses_menu, O_IGNORECASE);
	set_menu_mark(curses_menu, " ");
	set_menu_fore(curses_menu, attributes[MAIN_MENU_FORE]);
	set_menu_back(curses_menu, attributes[MAIN_MENU_BACK]);
	set_menu_grey(curses_menu, attributes[MAIN_MENU_GREY]);

	set_config_filename(conf_get_configname());
	setup_windows();

	/* check for KEY_FUNC(1) */
	if (has_key(KEY_F(1)) == FALSE) {
		show_scroll_win(main_window,
				"Instructions",
				menu_no_f_instructions);
	}

	conf_set_message_callback(conf_message_callback);
	/* do the work */
	while (!global_exit) {
		conf(&rootmenu);
		if (!global_exit && do_exit() == 0)
			break;
	}
	/* ok, we are done */
	unpost_menu(curses_menu);
	free_menu(curses_menu);
	delwin(main_window);
	clear();
	refresh();
	endwin();
	return 0;
}