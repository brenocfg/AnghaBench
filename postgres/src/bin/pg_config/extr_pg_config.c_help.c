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
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 

__attribute__((used)) static void
help(void)
{
	printf(_("\n%s provides information about the installed version of PostgreSQL.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]...\n\n"), progname);
	printf(_("Options:\n"));
	printf(_("  --bindir              show location of user executables\n"));
	printf(_("  --docdir              show location of documentation files\n"));
	printf(_("  --htmldir             show location of HTML documentation files\n"));
	printf(_("  --includedir          show location of C header files of the client\n"
			 "                        interfaces\n"));
	printf(_("  --pkgincludedir       show location of other C header files\n"));
	printf(_("  --includedir-server   show location of C header files for the server\n"));
	printf(_("  --libdir              show location of object code libraries\n"));
	printf(_("  --pkglibdir           show location of dynamically loadable modules\n"));
	printf(_("  --localedir           show location of locale support files\n"));
	printf(_("  --mandir              show location of manual pages\n"));
	printf(_("  --sharedir            show location of architecture-independent support files\n"));
	printf(_("  --sysconfdir          show location of system-wide configuration files\n"));
	printf(_("  --pgxs                show location of extension makefile\n"));
	printf(_("  --configure           show options given to \"configure\" script when\n"
			 "                        PostgreSQL was built\n"));
	printf(_("  --cc                  show CC value used when PostgreSQL was built\n"));
	printf(_("  --cppflags            show CPPFLAGS value used when PostgreSQL was built\n"));
	printf(_("  --cflags              show CFLAGS value used when PostgreSQL was built\n"));
	printf(_("  --cflags_sl           show CFLAGS_SL value used when PostgreSQL was built\n"));
	printf(_("  --ldflags             show LDFLAGS value used when PostgreSQL was built\n"));
	printf(_("  --ldflags_ex          show LDFLAGS_EX value used when PostgreSQL was built\n"));
	printf(_("  --ldflags_sl          show LDFLAGS_SL value used when PostgreSQL was built\n"));
	printf(_("  --libs                show LIBS value used when PostgreSQL was built\n"));
	printf(_("  --version             show the PostgreSQL version\n"));
	printf(_("  -?, --help            show this help, then exit\n"));
	printf(_("\nWith no arguments, all known items are shown.\n\n"));
	printf(_("Report bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}