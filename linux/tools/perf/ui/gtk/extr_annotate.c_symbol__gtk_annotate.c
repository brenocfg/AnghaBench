#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct symbol {int /*<<< orphan*/  name; } ;
struct map {TYPE_1__* dso; } ;
struct hist_browser_timer {int dummy; } ;
struct evsel {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_6__ {int /*<<< orphan*/ * notebook; int /*<<< orphan*/ * main_window; } ;
struct TYPE_5__ {scalar_t__ annotate_warned; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_NOTEBOOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  annotation__default_options ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_label_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_main_quit ; 
 int /*<<< orphan*/  gtk_notebook_append_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_notebook_new () ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* perf_gtk__activate_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_gtk__annotate_symbol (int /*<<< orphan*/ *,struct symbol*,struct map*,struct evsel*,struct hist_browser_timer*) ; 
 scalar_t__ perf_gtk__is_active_context (TYPE_2__*) ; 
 int /*<<< orphan*/ * perf_gtk__setup_info_bar () ; 
 int /*<<< orphan*/ * perf_gtk__setup_statusbar () ; 
 int /*<<< orphan*/  perf_gtk__signal ; 
 TYPE_2__* pgctx ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int symbol__annotate (struct symbol*,struct map*,struct evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__calc_percent (struct symbol*,struct evsel*) ; 
 int /*<<< orphan*/  symbol__strerror_disassemble (struct symbol*,struct map*,int,char*,int) ; 
 int /*<<< orphan*/  ui__error (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int symbol__gtk_annotate(struct symbol *sym, struct map *map,
				struct evsel *evsel,
				struct hist_browser_timer *hbt)
{
	GtkWidget *window;
	GtkWidget *notebook;
	GtkWidget *scrolled_window;
	GtkWidget *tab_label;
	int err;

	if (map->dso->annotate_warned)
		return -1;

	err = symbol__annotate(sym, map, evsel, 0, &annotation__default_options, NULL);
	if (err) {
		char msg[BUFSIZ];
		symbol__strerror_disassemble(sym, map, err, msg, sizeof(msg));
		ui__error("Couldn't annotate %s: %s\n", sym->name, msg);
		return -1;
	}

	symbol__calc_percent(sym, evsel);

	if (perf_gtk__is_active_context(pgctx)) {
		window = pgctx->main_window;
		notebook = pgctx->notebook;
	} else {
		GtkWidget *vbox;
		GtkWidget *infobar;
		GtkWidget *statbar;

		signal(SIGSEGV, perf_gtk__signal);
		signal(SIGFPE,  perf_gtk__signal);
		signal(SIGINT,  perf_gtk__signal);
		signal(SIGQUIT, perf_gtk__signal);
		signal(SIGTERM, perf_gtk__signal);

		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "perf annotate");

		g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

		pgctx = perf_gtk__activate_context(window);
		if (!pgctx)
			return -1;

		vbox = gtk_vbox_new(FALSE, 0);
		notebook = gtk_notebook_new();
		pgctx->notebook = notebook;

		gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

		infobar = perf_gtk__setup_info_bar();
		if (infobar) {
			gtk_box_pack_start(GTK_BOX(vbox), infobar,
					   FALSE, FALSE, 0);
		}

		statbar = perf_gtk__setup_statusbar();
		gtk_box_pack_start(GTK_BOX(vbox), statbar, FALSE, FALSE, 0);

		gtk_container_add(GTK_CONTAINER(window), vbox);
	}

	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	tab_label = gtk_label_new(sym->name);

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
				       GTK_POLICY_AUTOMATIC,
				       GTK_POLICY_AUTOMATIC);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrolled_window,
				 tab_label);

	perf_gtk__annotate_symbol(scrolled_window, sym, map, evsel, hbt);
	return 0;
}