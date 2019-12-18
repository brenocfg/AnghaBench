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
 int MODE_DFLT ; 
 int MODE_JSON ; 
 int MODE_ZERO ; 
 int /*<<< orphan*/  SDB_OPTION_JOURNAL ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int base64decode () ; 
 int base64encode () ; 
 int createdb (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdiff (char const*,char const*) ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  insertkeys (int /*<<< orphan*/ ,char const**,int,char) ; 
 int jsonIndent () ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  save ; 
 int /*<<< orphan*/  sdb_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdb_dump (char const*,int) ; 
 int sdb_grep (char const*,int,char const*) ; 
 int /*<<< orphan*/  sdb_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_query (int /*<<< orphan*/ ,char const*) ; 
 int showcount (char const*) ; 
 int showusage (int) ; 
 int showversion () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int)) ; 
 char* stdin_slurp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  synchronize (int) ; 
 int /*<<< orphan*/  terminate (int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

int main(int argc, const char **argv) {
	char *line;
	const char *arg, *grep = NULL;
	int i, fmt = MODE_DFLT;
	int db0 = 1, argi = 1;
	bool interactive = false;

	/* terminate flags */
	if (argc < 2) {
		return showusage (1);
	}
	arg = argv[1];

	if (arg[0] == '-') {// && arg[1] && arg[2]==0) {
		switch (arg[1]) {
		case 0:
			/* no-op */
			break;
		case '0':
			fmt = MODE_ZERO;
			db0++;
			argi++;
			if (db0 >= argc) {
				return showusage (1);
			}
			break;
		case 'g':
			db0 += 2;
			if (db0 >= argc) {
				return showusage (1);
			}
			grep = argv[2];
			argi += 2;
			break;
		case 'J':
			options |= SDB_OPTION_JOURNAL;
			db0++;
			argi++;
			if (db0 >= argc) {
				return showusage (1);
			}
			break;
		case 'c': return (argc < 3)? showusage (1): showcount (argv[2]);
		case 'v': return showversion ();
		case 'h': return showusage (2);
		case 'e': return base64encode ();
		case 'd': return base64decode ();
		case 'D':
			if (argc == 4) {
				return dbdiff (argv[2], argv[3]) ? 0 : 1;
			}
			return showusage (0);
		case 'j':
			if (argc > 2) {
				return sdb_dump (argv[db0 + 1], MODE_JSON);
			}
			return jsonIndent ();
		default:
			eprintf ("Invalid flag %s\n", arg);
			break;
		}
	}

	/* sdb - */
	if (argi == 1 && !strcmp (argv[argi], "-")) {
		/* no database */
		argv[argi] = "";
		if (argc == db0 + 1) {
			interactive = true;
			/* if no argument passed */
			argv[argi] = "-";
			argc++;
			argi++;
		}
	}
	/* sdb dbname */
	if (argc - 1 == db0) {
		if (grep) {
			return sdb_grep (argv[db0], fmt, grep);
		}
		return sdb_dump (argv[db0], fmt);
	}
#if USE_MMAN
	signal (SIGINT, terminate);
	signal (SIGHUP, synchronize);
#endif
	int ret = 0;
	if (interactive || !strcmp (argv[db0 + 1], "-")) {
		if ((s = sdb_new (NULL, argv[db0], 0))) {
			sdb_config (s, options);
			int kvs = db0 + 2;
			if (kvs < argc) {
				save |= insertkeys (s, argv + argi + 2, argc - kvs, '-');
			}
			for (; (line = stdin_slurp (NULL));) {
				save |= sdb_query (s, line);
				if (fmt) {
					fflush (stdout);
					write (1, "", 1);
				}
				free (line);
			}
		}
	} else if (!strcmp (argv[db0 + 1], "=")) {
		ret = createdb (argv[db0], NULL, 0);
	} else {
		s = sdb_new (NULL, argv[db0], 0);
		if (!s) {
			return 1;
		}
		sdb_config (s, options);
		for (i = db0 + 1; i < argc; i++) {
			save |= sdb_query (s, argv[i]);
			if (fmt) {
				fflush (stdout);
				write (1, "", 1);
			}
		}
	}
	terminate (ret);
	return ret;
}