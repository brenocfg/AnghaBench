#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  mmask_t ;
struct TYPE_4__ {int blkorder; int showdetail; int filtermode; int cliopener; int filtercmd; int showhidden; int nonavopen; int picker; int pickraw; int useeditor; int trash; int /*<<< orphan*/  autoselect; int /*<<< orphan*/  filter_re; int /*<<< orphan*/  mtime; } ;
struct TYPE_3__ {char color; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_MAX ; 
 int CTX_MAX ; 
 int /*<<< orphan*/  DPRINTF_S (char*) ; 
 int /*<<< orphan*/  DPRINTF_U (scalar_t__) ; 
 size_t EDITOR ; 
 int FALSE ; 
 int /*<<< orphan*/  F_NOWAIT ; 
 int /*<<< orphan*/  IN_NONBLOCK ; 
 int /*<<< orphan*/  LC_ALL ; 
 size_t NNNLVL ; 
 size_t NNN_BMS ; 
 size_t NNN_CONTEXT_COLORS ; 
 size_t NNN_COPIER ; 
 size_t NNN_IDLE_TIMEOUT ; 
 size_t NNN_OPENER ; 
 size_t NNN_TRASH ; 
 size_t NNN_USE_EDITOR ; 
 size_t OPENER ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 size_t PAGER ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  PLUGIN_MAX ; 
 size_t SHELL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 size_t STR_INVBM_KEY ; 
 int /*<<< orphan*/  S_BLKSIZE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 char* VERSION ; 
 size_t VISUAL ; 
 int _FAILURE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_shift ; 
 int /*<<< orphan*/  bmstr ; 
 int /*<<< orphan*/  bookmark ; 
 int /*<<< orphan*/  browse (char*,char*) ; 
 TYPE_2__ cfg ; 
 int /*<<< orphan*/  cfgdir ; 
 int /*<<< orphan*/  check_key_collision () ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/ * cmpfn ; 
 char* copier ; 
 char* cp ; 
 char* editor ; 
 int /*<<< orphan*/  enabledbg () ; 
 char** env_cfg ; 
 char** envs ; 
 scalar_t__ event_fd ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exitcurses () ; 
 int /*<<< orphan*/  ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * filterfn ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_buf ; 
 TYPE_1__* g_ctx ; 
 void* g_selpath ; 
 char* get_kv_val (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 char* home ; 
 scalar_t__ idletimeout ; 
 int /*<<< orphan*/  initcurses (int /*<<< orphan*/ *) ; 
 char* initpath ; 
 scalar_t__ inotify_fd ; 
 scalar_t__ inotify_init1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_rm_watch (scalar_t__,scalar_t__) ; 
 scalar_t__ inotify_wd ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ kq ; 
 scalar_t__ kqueue () ; 
 char** messages ; 
 int /*<<< orphan*/  mkpath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousemask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mv ; 
 int /*<<< orphan*/  nftw_fn ; 
 int open (char*,int,int) ; 
 char* opener ; 
 char* optarg ; 
 int optind ; 
 char* pager ; 
 int /*<<< orphan*/  parsekvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plug ; 
 int /*<<< orphan*/  pluginstr ; 
 int /*<<< orphan*/  printent_long ; 
 int /*<<< orphan*/ * printptr ; 
 int /*<<< orphan*/  pselbuf ; 
 int /*<<< orphan*/  read_history (int /*<<< orphan*/ ) ; 
 void* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rl_bind_key (char,int /*<<< orphan*/ ) ; 
 scalar_t__ rl_change_environment ; 
 int /*<<< orphan*/  rl_complete ; 
 int /*<<< orphan*/  rl_menu_complete ; 
 int /*<<< orphan*/  rl_variable_bind (char*,char*) ; 
 scalar_t__ selbufpos ; 
 int seltofile (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_tmp_path () ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setup_config () ; 
 char* shell ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spawn (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  sum_bsizes ; 
 int /*<<< orphan*/  unlink (void*) ; 
 int /*<<< orphan*/  usage () ; 
 char** utils ; 
 int /*<<< orphan*/  visible_str ; 
 int /*<<< orphan*/  write_history (int /*<<< orphan*/ ) ; 
 scalar_t__ xatoi (char*) ; 
 int /*<<< orphan*/  xdiraccess (char*) ; 
 int /*<<< orphan*/  xerror () ; 
 char* xgetenv (char*,char*) ; 
 scalar_t__ xgetenv_set (char*) ; 
 int /*<<< orphan*/  xitoa (scalar_t__) ; 
 int /*<<< orphan*/  xstrverscasecmp ; 

int main(int argc, char *argv[])
{
	mmask_t mask;
	char *arg = NULL;
	char *session = NULL;
	int opt;
#ifdef __linux__
	bool progress = FALSE;
#endif

	while ((opt = getopt(argc, argv, "HSKiab:cde:fnop:rstvh")) != -1) {
		switch (opt) {
		case 'S':
			cfg.blkorder = 1;
			nftw_fn = sum_bsizes;
			blk_shift = ffs(S_BLKSIZE) - 1; // fallthrough
		case 'd':
			cfg.showdetail = 1;
			printptr = &printent_long;
			break;
		case 'i':
			cfg.filtermode = 1;
			break;
		case 'a':
			cfg.mtime = 0;
			break;
		case 'b':
			arg = optarg;
			break;
		case 'c':
			cfg.cliopener = 1;
			break;
		case 'e':
			session = optarg;
			break;
		case 'f':
			cfg.filtercmd = 1;
			break;
		case 'H':
			cfg.showhidden = 1;
			break;
		case 'n':
			cmpfn = &xstrverscasecmp;
			break;
		case 'o':
			cfg.nonavopen = 1;
			break;
		case 'p':
			cfg.picker = 1;
			if (optarg[0] == '-' && optarg[1] == '\0')
				cfg.pickraw = 1;
			else {
				int fd = open(optarg, O_WRONLY | O_CREAT, 0600);

				if (fd == -1) {
					xerror();
					return _FAILURE;
				}

				close(fd);
				g_selpath = realpath(optarg, NULL);
				unlink(g_selpath);
			}
			break;
		case 'r':
#ifdef __linux__
			progress = TRUE;
#endif
			break;
		case 's':
			cfg.filter_re = 0;
			filterfn = &visible_str;
			break;
		case 't':
			cfg.autoselect = 0;
			break;
		case 'K':
			check_key_collision();
			return _SUCCESS;
		case 'v':
			fprintf(stdout, "%s\n", VERSION);
			return _SUCCESS;
		case 'h':
			usage();
			return _SUCCESS;
		default:
			usage();
			return _FAILURE;
		}
	}

	/* Confirm we are in a terminal */
	if (!cfg.picker && !(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)))
		exit(1);

	/* Get the context colors; copier used as tmp var */
	copier = xgetenv(env_cfg[NNN_CONTEXT_COLORS], "4444");
	opt = 0;
	while (opt < CTX_MAX) {
		if (*copier) {
			if (*copier < '0' || *copier > '7') {
				fprintf(stderr, "0 <= code <= 7\n");
				return _FAILURE;
			}

			g_ctx[opt].color = *copier - '0';
			++copier;
		} else
			g_ctx[opt].color = 4;

		++opt;
	}

#ifdef DBGMODE
	enabledbg();
	DPRINTF_S(VERSION);
#endif

	atexit(cleanup);

	home = getenv("HOME");
	if (!home) {
		fprintf(stderr, "set HOME\n");
		return _FAILURE;
	}
	DPRINTF_S(home);

	if (!setup_config())
		return _FAILURE;

	/* Get custom opener, if set */
	opener = xgetenv(env_cfg[NNN_OPENER], utils[OPENER]);
	DPRINTF_S(opener);

	/* Parse bookmarks string */
	if (!parsekvpair(bookmark, &bmstr, env_cfg[NNN_BMS], BM_MAX)) {
		fprintf(stderr, "%s\n", env_cfg[NNN_BMS]);
		return _FAILURE;
	}

	/* Parse plugins string */
	if (!parsekvpair(plug, &pluginstr, "NNN_PLUG", PLUGIN_MAX)) {
		fprintf(stderr, "%s\n", "NNN_PLUG");
		return _FAILURE;
	}

	if (arg) { /* Open a bookmark directly */
		if (!arg[1]) /* Bookmarks keys are single char */
			initpath = get_kv_val(bookmark, NULL, *arg, BM_MAX, TRUE);

		if (!initpath) {
			fprintf(stderr, "%s\n", messages[STR_INVBM_KEY]);
			return _FAILURE;
		}
	} else if (argc == optind) {
		/* Start in the current directory */
		initpath = getcwd(NULL, PATH_MAX);
		if (!initpath)
			initpath = "/";
	} else {
		arg = argv[optind];
		if (strlen(arg) > 7 && !strncmp(arg, "file://", 7))
			arg = arg + 7;
		initpath = realpath(arg, NULL);
		DPRINTF_S(initpath);
		if (!initpath) {
			xerror();
			return _FAILURE;
		}

		/*
		 * If nnn is set as the file manager, applications may try to open
		 * files by invoking nnn. In that case pass the file path to the
		 * desktop opener and exit.
		 */
		struct stat sb;

		if (stat(initpath, &sb) == -1) {
			xerror();
			return _FAILURE;
		}

		if (S_ISREG(sb.st_mode)) {
			spawn(opener, arg, NULL, NULL, F_NOWAIT);
			return _SUCCESS;
		}
	}

	/* Edit text in EDITOR if opted (and opener is not all-CLI) */
	if (!cfg.cliopener && xgetenv_set(env_cfg[NNN_USE_EDITOR]))
		cfg.useeditor = 1;

	/* Get VISUAL/EDITOR */
	editor = xgetenv(envs[VISUAL], xgetenv(envs[EDITOR], "vi"));
	DPRINTF_S(getenv(envs[VISUAL]));
	DPRINTF_S(getenv(envs[EDITOR]));
	DPRINTF_S(editor);

	/* Get PAGER */
	pager = xgetenv(envs[PAGER], "less");
	DPRINTF_S(pager);

	/* Get SHELL */
	shell = xgetenv(envs[SHELL], "sh");
	DPRINTF_S(shell);

	DPRINTF_S(getenv("PWD"));

#ifdef LINUX_INOTIFY
	/* Initialize inotify */
	inotify_fd = inotify_init1(IN_NONBLOCK);
	if (inotify_fd < 0) {
		xerror();
		return _FAILURE;
	}
#elif defined(BSD_KQUEUE)
	kq = kqueue();
	if (kq < 0) {
		xerror();
		return _FAILURE;
	}
#endif

	/* Set nnn nesting level, idletimeout used as tmp var */
	idletimeout = xatoi(getenv(env_cfg[NNNLVL]));
	setenv(env_cfg[NNNLVL], xitoa(++idletimeout), 1);

	/* Get locker wait time, if set */
	idletimeout = xatoi(getenv(env_cfg[NNN_IDLE_TIMEOUT]));
	DPRINTF_U(idletimeout);

	if (xgetenv_set(env_cfg[NNN_TRASH]))
		cfg.trash = 1;

	/* Prefix for temporary files */
	if (!set_tmp_path())
		return _FAILURE;

	/* Get the clipboard copier, if set */
	copier = getenv(env_cfg[NNN_COPIER]);

#ifdef __linux__
	if (!progress) {
		cp[5] = cp[4];
		cp[2] = cp[4] = ' ';

		mv[5] = mv[4];
		mv[2] = mv[4] = ' ';
	}
#endif

	/* Ignore/handle certain signals */
	struct sigaction act = {.sa_handler = sigint_handler};

	if (sigaction(SIGINT, &act, NULL) < 0) {
		xerror();
		return _FAILURE;
	}
	signal(SIGQUIT, SIG_IGN);

	/* Test initial path */
	if (!xdiraccess(initpath)) {
		xerror();
		return _FAILURE;
	}

#ifndef NOLOCALE
	/* Set locale */
	setlocale(LC_ALL, "");
#endif

#ifndef NORL
#if RL_READLINE_VERSION >= 0x0603
	/* readline would overwrite the WINCH signal hook */
	rl_change_environment = 0;
#endif
	/* Bind TAB to cycling */
	rl_variable_bind("completion-ignore-case", "on");
#ifdef __linux__
	rl_bind_key('\t', rl_menu_complete);
#else
	rl_bind_key('\t', rl_complete);
#endif
	mkpath(cfgdir, ".history", g_buf);
	read_history(g_buf);
#endif

	if (!initcurses(&mask))
		return _FAILURE;

	browse(initpath, session);
	mousemask(mask, NULL);
	exitcurses();

#ifndef NORL
	mkpath(cfgdir, ".history", g_buf);
	write_history(g_buf);
#endif

	if (cfg.pickraw) {
		if (selbufpos) {
			opt = seltofile(1, NULL);
			if (opt != (int)(selbufpos))
				xerror();
		}
	} else if (!cfg.picker && g_selpath)
		unlink(g_selpath);

	/* Free the selection buffer */
	free(pselbuf);

#ifdef LINUX_INOTIFY
	/* Shutdown inotify */
	if (inotify_wd >= 0)
		inotify_rm_watch(inotify_fd, inotify_wd);
	close(inotify_fd);
#elif defined(BSD_KQUEUE)
	if (event_fd >= 0)
		close(event_fd);
	close(kq);
#endif

	return _SUCCESS;
}