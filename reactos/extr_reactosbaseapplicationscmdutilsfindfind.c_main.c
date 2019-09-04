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
typedef  int /*<<< orphan*/  wszMessage ;
struct _finddata_t {char* name; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CharToOemW (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_CANNOT_OPEN ; 
 int /*<<< orphan*/  IDS_NO_SUCH_FILE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _findclose (int) ; 
 int _findfirst (char*,struct _finddata_t*) ; 
 scalar_t__ _findnext (int,struct _finddata_t*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int find_str (char*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  usage () ; 

int
main (int argc, char **argv)
{
  char *opt, *needle = NULL;
  int ret = 0;
  WCHAR wszMessage[4096];
  char oemMessage[4096];

  int invert_search = 0;		/* flag to invert the search */
  int count_lines = 0;			/* flag to whether/not count lines */
  int number_output = 0;		/* flag to print line numbers */
  int ignore_case = 0;			/* flag to be case insensitive */

  FILE *pfile;				/* file pointer */
  int hfind;				/* search handle */
  struct _finddata_t finddata;		/* _findfirst, filenext block */

  /* Scan the command line */
  while ((--argc) && (needle == NULL))
    {
      if (*(opt = *++argv) == '/')
        {
          switch (opt[1])
	    {
	      case 'c':
	      case 'C':		/* Count */
	        count_lines = 1;
	        break;

	      case 'i':
	      case 'I':		/* Ignore */
	        ignore_case = 1;
	        break;

	      case 'n':
	      case 'N':		/* Number */
	        number_output = 1;
	        break;

	      case 'v':
	      case 'V':		/* Not with */
	        invert_search = 1;
	        break;

	      default:
	        usage ();
	        exit (2);		/* syntax error .. return error 2 */
	        break;
	    }
        }
      else
        {
          /* Get the string */
	  if (needle == NULL)
	    {
              /* Assign the string to find */
              needle = *argv;
	    }
	}
    }

  /* Check for search string */
  if (needle == NULL)
    {
      /* No string? */
      usage ();
      exit (1);
    }

  /* Scan the files for the string */
  if (argc == 0)
    {
      ret = find_str (needle, stdin, invert_search, count_lines,
                      number_output, ignore_case);
    }

  while (--argc >= 0)
    {
      hfind = _findfirst (*++argv, &finddata);
      if (hfind < 0)
	{
	  /* We were not able to find a file. Display a message and
	     set the exit status. */
	  LoadStringW (GetModuleHandleW (NULL), IDS_NO_SUCH_FILE, wszMessage, sizeof(wszMessage) / sizeof(wszMessage[0]));
	  CharToOemW (wszMessage, oemMessage);
	  fprintf (stderr, oemMessage, *argv);
	}
      else
        {
          /* repeat find next file to match the filemask */
	  do
            {
              /* We have found a file, so try to open it */
	      if ((pfile = fopen (finddata.name, "r")) != NULL)
	        {
	          printf ("---------------- %s\n", finddata.name);
	          ret = find_str (needle, pfile, invert_search, count_lines,
	                          number_output, ignore_case);
	          fclose (pfile);
	        }
 	      else
	        {
	          LoadStringW (GetModuleHandleW (NULL), IDS_CANNOT_OPEN, wszMessage, sizeof(wszMessage) / sizeof(wszMessage[0]));
	          CharToOemW (wszMessage, oemMessage);
	          fprintf (stderr, oemMessage,
		           finddata.name);
                }
	    }
          while (_findnext(hfind, &finddata) > 0);
        }
      _findclose(hfind);
    } /* for each argv */

 /* RETURN: If the string was found at least once, returns 0.
  * If the string was not found at all, returns 1.
  * (Note that find_str.c returns the exact opposite values.)
  */
  exit ( (ret ? 0 : 1) );
}