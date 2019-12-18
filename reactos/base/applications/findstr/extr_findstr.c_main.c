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
struct _finddata_t {char* name; } ;
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CharToOem (char*,char*) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_CANNOT_OPEN ; 
 int /*<<< orphan*/  IDS_NO_SUCH_FILE ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _findclose (int) ; 
 int _findfirst (char*,struct _finddata_t*) ; 
 scalar_t__ _findnext (int,struct _finddata_t*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int find_str (char*,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int,int,int,int) ; 
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
  TCHAR lpMessage[4096];

  int invert_search = 0;		/* flag to invert the search */
  int count_lines = 0;			/* flag to whether/not count lines */
  int number_output = 0;		/* flag to print line numbers */
  int ignore_case = 0;			/* flag to be case insensitive */
  int at_start = 0;				/* flag to Match if at the beginning of a line. */
  int at_end = 0;	        	/* flag to Match if at the beginning of a line. */
  int reg_express = 0;		   /* flag to use/not use regular expressions */
  int exact_match = 0;			/* flag to be exact match */
  int sub_dirs= 0;				/* this and all subdirectories */
  int only_fname= 0;			/* print only the name of the file*/
  int literal_search=0;

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
	      case 'b':
	      case 'B':		/* Matches pattern if at the beginning of a line */
	        at_start = 1;
	        break;
			
	      //case 'c':
	      //case 'C':		/* Literal? */
	      //  literal_search = 1;
	      //  break;

	      case 'e':
	      case 'E':		/* matches pattern if at end of line */
	        at_end = 1;
	        break;
			
	      case 'i':
	      case 'I':		/* Ignore */
	        ignore_case = 1;
	        break;

	      case 'm':
	      case 'M':		/* only filename */
	        only_fname = 1;
	        break;			
			
	      case 'n':
	      case 'N':		/* Number */
	        number_output = 1;
	        break;
			
	      case 'r':
	      case 'R':		/* search strings as regular expressions */
	        reg_express = 1;
	        break;	

	      case 's':
	      case 'S':		/* search files in child directory too*/
	        sub_dirs = 1;
	        break;				

	      case 'v':
	      case 'V':		/* Not with */
	        invert_search = 1;
	        break;

	      case 'x':
	      case 'X':		/* exact match */
	        exact_match = 1;
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
                      number_output, ignore_case, at_start, literal_search, at_end, reg_express, exact_match,
					  sub_dirs, only_fname);
    }

  while (--argc >= 0)
    {
      hfind = _findfirst (*++argv, &finddata);
      if (hfind < 0)
	{
	  /* We were not able to find a file. Display a message and
	     set the exit status. */
	  LoadString( GetModuleHandle(NULL), IDS_NO_SUCH_FILE, (LPTSTR)lpMessage, 4096);
	  CharToOem(lpMessage, lpMessage);
	  fprintf (stderr, lpMessage, *argv);//
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
                      number_output, ignore_case, at_start, literal_search, at_end, reg_express, exact_match,
					  sub_dirs, only_fname);
	          fclose (pfile);
	        }
 	      else
	        {
	          LoadString(GetModuleHandle(NULL), IDS_CANNOT_OPEN, (LPTSTR)lpMessage, 4096);
	          CharToOem(lpMessage, lpMessage);
	          fprintf (stderr, lpMessage,
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