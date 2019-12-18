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
 int PG_UTF8 ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  check_locale_encoding (char*,int) ; 
 int /*<<< orphan*/  encoding ; 
 int encodingid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int get_encoding_id (int /*<<< orphan*/ ) ; 
 char* lc_collate ; 
 char* lc_ctype ; 
 char* lc_messages ; 
 char* lc_monetary ; 
 char* lc_numeric ; 
 char* lc_time ; 
 char* pg_encoding_to_char (int) ; 
 int pg_get_encoding_from_locale (char*,int) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,...) ; 
 int /*<<< orphan*/  pg_valid_server_encoding_id (int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  setlocales () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

void
setup_locale_encoding(void)
{
	setlocales();

	if (strcmp(lc_ctype, lc_collate) == 0 &&
		strcmp(lc_ctype, lc_time) == 0 &&
		strcmp(lc_ctype, lc_numeric) == 0 &&
		strcmp(lc_ctype, lc_monetary) == 0 &&
		strcmp(lc_ctype, lc_messages) == 0)
		printf(_("The database cluster will be initialized with locale \"%s\".\n"), lc_ctype);
	else
	{
		printf(_("The database cluster will be initialized with locales\n"
				 "  COLLATE:  %s\n"
				 "  CTYPE:    %s\n"
				 "  MESSAGES: %s\n"
				 "  MONETARY: %s\n"
				 "  NUMERIC:  %s\n"
				 "  TIME:     %s\n"),
			   lc_collate,
			   lc_ctype,
			   lc_messages,
			   lc_monetary,
			   lc_numeric,
			   lc_time);
	}

	if (!encoding)
	{
		int			ctype_enc;

		ctype_enc = pg_get_encoding_from_locale(lc_ctype, true);

		if (ctype_enc == -1)
		{
			/* Couldn't recognize the locale's codeset */
			pg_log_error("could not find suitable encoding for locale \"%s\"",
						 lc_ctype);
			fprintf(stderr, _("Rerun %s with the -E option.\n"), progname);
			fprintf(stderr, _("Try \"%s --help\" for more information.\n"),
					progname);
			exit(1);
		}
		else if (!pg_valid_server_encoding_id(ctype_enc))
		{
			/*
			 * We recognized it, but it's not a legal server encoding. On
			 * Windows, UTF-8 works with any locale, so we can fall back to
			 * UTF-8.
			 */
#ifdef WIN32
			encodingid = PG_UTF8;
			printf(_("Encoding \"%s\" implied by locale is not allowed as a server-side encoding.\n"
					 "The default database encoding will be set to \"%s\" instead.\n"),
				   pg_encoding_to_char(ctype_enc),
				   pg_encoding_to_char(encodingid));
#else
			pg_log_error("locale \"%s\" requires unsupported encoding \"%s\"",
						 lc_ctype, pg_encoding_to_char(ctype_enc));
			fprintf(stderr,
					_("Encoding \"%s\" is not allowed as a server-side encoding.\n"
					  "Rerun %s with a different locale selection.\n"),
					pg_encoding_to_char(ctype_enc), progname);
			exit(1);
#endif
		}
		else
		{
			encodingid = ctype_enc;
			printf(_("The default database encoding has accordingly been set to \"%s\".\n"),
				   pg_encoding_to_char(encodingid));
		}
	}
	else
		encodingid = get_encoding_id(encoding);

	if (!check_locale_encoding(lc_ctype, encodingid) ||
		!check_locale_encoding(lc_collate, encodingid))
		exit(1);				/* check_locale_encoding printed the error */

}