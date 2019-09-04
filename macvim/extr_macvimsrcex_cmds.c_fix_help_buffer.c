#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int linenr_T ;
typedef  int /*<<< orphan*/  colnr_T ;
typedef  char char_u ;
struct TYPE_4__ {int ml_line_count; } ;
struct TYPE_5__ {TYPE_1__ b_ml; int /*<<< orphan*/  b_fname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EW_FILE ; 
 int EW_SILENT ; 
 int FALSE ; 
 scalar_t__ FPC_SAME ; 
 int /*<<< orphan*/  FreeWild (int,char**) ; 
 int /*<<< orphan*/  IOSIZE ; 
 char* IObuff ; 
 int /*<<< orphan*/  MAXPATHL ; 
 char NUL ; 
 int /*<<< orphan*/  NameBuff ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  OPT_LOCAL ; 
 int /*<<< orphan*/  STRCAT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ STRLEN (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  add_pathsep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_option_part (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* curbuf ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fnamecmp (char*,char*) ; 
 scalar_t__ fullpathcmp (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gen_expand_wildcards (int,int /*<<< orphan*/ *,int*,char***,int) ; 
 char* gettail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mch_fopen (char*,char*) ; 
 int /*<<< orphan*/  ml_append (int,char*,int /*<<< orphan*/ ,int) ; 
 char* ml_get_buf (TYPE_2__*,int,int) ; 
 char* p_rtp ; 
 int /*<<< orphan*/  set_option_value (char*,long,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  vim_fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 char* vim_getenv (char*,int*) ; 
 int /*<<< orphan*/  vim_iswhite (char) ; 
 char* vim_strchr (char*,char) ; 

void
fix_help_buffer()
{
    linenr_T	lnum;
    char_u	*line;
    int		in_example = FALSE;
    int		len;
    char_u	*fname;
    char_u	*p;
    char_u	*rt;
    int		mustfree;

    /* set filetype to "help". */
    set_option_value((char_u *)"ft", 0L, (char_u *)"help", OPT_LOCAL);

#ifdef FEAT_SYN_HL
    if (!syntax_present(curwin))
#endif
    {
	for (lnum = 1; lnum <= curbuf->b_ml.ml_line_count; ++lnum)
	{
	    line = ml_get_buf(curbuf, lnum, FALSE);
	    len = (int)STRLEN(line);
	    if (in_example && len > 0 && !vim_iswhite(line[0]))
	    {
		/* End of example: non-white or '<' in first column. */
		if (line[0] == '<')
		{
		    /* blank-out a '<' in the first column */
		    line = ml_get_buf(curbuf, lnum, TRUE);
		    line[0] = ' ';
		}
		in_example = FALSE;
	    }
	    if (!in_example && len > 0)
	    {
		if (line[len - 1] == '>' && (len == 1 || line[len - 2] == ' '))
		{
		    /* blank-out a '>' in the last column (start of example) */
		    line = ml_get_buf(curbuf, lnum, TRUE);
		    line[len - 1] = ' ';
		    in_example = TRUE;
		}
		else if (line[len - 1] == '~')
		{
		    /* blank-out a '~' at the end of line (header marker) */
		    line = ml_get_buf(curbuf, lnum, TRUE);
		    line[len - 1] = ' ';
		}
	    }
	}
    }

    /*
     * In the "help.txt" and "help.abx" file, add the locally added help
     * files.  This uses the very first line in the help file.
     */
    fname = gettail(curbuf->b_fname);
    if (fnamecmp(fname, "help.txt") == 0
#ifdef FEAT_MULTI_LANG
	|| (fnamencmp(fname, "help.", 5) == 0
	    && ASCII_ISALPHA(fname[5])
	    && ASCII_ISALPHA(fname[6])
	    && TOLOWER_ASC(fname[7]) == 'x'
	    && fname[8] == NUL)
#endif
	)
    {
	for (lnum = 1; lnum < curbuf->b_ml.ml_line_count; ++lnum)
	{
	    line = ml_get_buf(curbuf, lnum, FALSE);
	    if (strstr((char *)line, "*local-additions*") == NULL)
		continue;

	    /* Go through all directories in 'runtimepath', skipping
	     * $VIMRUNTIME. */
	    p = p_rtp;
	    while (*p != NUL)
	    {
		copy_option_part(&p, NameBuff, MAXPATHL, ",");
		mustfree = FALSE;
		rt = vim_getenv((char_u *)"VIMRUNTIME", &mustfree);
		if (fullpathcmp(rt, NameBuff, FALSE) != FPC_SAME)
		{
		    int		fcount;
		    char_u	**fnames;
		    FILE	*fd;
		    char_u	*s;
		    int		fi;
#ifdef FEAT_MBYTE
		    vimconv_T	vc;
		    char_u	*cp;
#endif

		    /* Find all "doc/ *.txt" files in this directory. */
		    add_pathsep(NameBuff);
#ifdef FEAT_MULTI_LANG
		    STRCAT(NameBuff, "doc/*.??[tx]");
#else
		    STRCAT(NameBuff, "doc/*.txt");
#endif
		    if (gen_expand_wildcards(1, &NameBuff, &fcount,
					 &fnames, EW_FILE|EW_SILENT) == OK
			    && fcount > 0)
		    {
#ifdef FEAT_MULTI_LANG
			int	i1;
			int	i2;
			char_u	*f1;
			char_u	*f2;
			char_u	*t1;
			char_u	*e1;
			char_u	*e2;

			/* If foo.abx is found use it instead of foo.txt in
			 * the same directory. */
			for (i1 = 0; i1 < fcount; ++i1)
			{
			    for (i2 = 0; i2 < fcount; ++i2)
			    {
				if (i1 == i2)
				    continue;
				if (fnames[i1] == NULL || fnames[i2] == NULL)
				    continue;
				f1 = fnames[i1];
				f2 = fnames[i2];
				t1 = gettail(f1);
				if (fnamencmp(f1, f2, t1 - f1) != 0)
				    continue;
				e1 = vim_strrchr(t1, '.');
				e2 = vim_strrchr(gettail(f2), '.');
				if (e1 == NUL || e2 == NUL)
				    continue;
				if (fnamecmp(e1, ".txt") != 0
				    && fnamecmp(e1, fname + 4) != 0)
				{
				    /* Not .txt and not .abx, remove it. */
				    vim_free(fnames[i1]);
				    fnames[i1] = NULL;
				    continue;
				}
				if (fnamencmp(f1, f2, e1 - f1) != 0)
				    continue;
				if (fnamecmp(e1, ".txt") == 0
				    && fnamecmp(e2, fname + 4) == 0)
				{
				    /* use .abx instead of .txt */
				    vim_free(fnames[i1]);
				    fnames[i1] = NULL;
				}
			    }
			}
#endif
			for (fi = 0; fi < fcount; ++fi)
			{
			    if (fnames[fi] == NULL)
				continue;
			    fd = mch_fopen((char *)fnames[fi], "r");
			    if (fd != NULL)
			    {
				vim_fgets(IObuff, IOSIZE, fd);
				if (IObuff[0] == '*'
					&& (s = vim_strchr(IObuff + 1, '*'))
								  != NULL)
				{
#ifdef FEAT_MBYTE
				    int	this_utf = MAYBE;
#endif
				    /* Change tag definition to a
				     * reference and remove <CR>/<NL>. */
				    IObuff[0] = '|';
				    *s = '|';
				    while (*s != NUL)
				    {
					if (*s == '\r' || *s == '\n')
					    *s = NUL;
#ifdef FEAT_MBYTE
					/* The text is utf-8 when a byte
					 * above 127 is found and no
					 * illegal byte sequence is found.
					 */
					if (*s >= 0x80 && this_utf != FALSE)
					{
					    int	l;

					    this_utf = TRUE;
					    l = utf_ptr2len(s);
					    if (l == 1)
						this_utf = FALSE;
					    s += l - 1;
					}
#endif
					++s;
				    }
#ifdef FEAT_MBYTE
				    /* The help file is latin1 or utf-8;
				     * conversion to the current
				     * 'encoding' may be required. */
				    vc.vc_type = CONV_NONE;
				    convert_setup(&vc, (char_u *)(
						this_utf == TRUE ? "utf-8"
						      : "latin1"), p_enc);
				    if (vc.vc_type == CONV_NONE)
					/* No conversion needed. */
					cp = IObuff;
				    else
				    {
					/* Do the conversion.  If it fails
					 * use the unconverted text. */
					cp = string_convert(&vc, IObuff,
								    NULL);
					if (cp == NULL)
					    cp = IObuff;
				    }
				    convert_setup(&vc, NULL, NULL);

				    ml_append(lnum, cp, (colnr_T)0, FALSE);
				    if (cp != IObuff)
					vim_free(cp);
#else
				    ml_append(lnum, IObuff, (colnr_T)0,
								   FALSE);
#endif
				    ++lnum;
				}
				fclose(fd);
			    }
			}
			FreeWild(fcount, fnames);
		    }
		}
		if (mustfree)
		    vim_free(rt);
	    }
	    break;
	}
    }
}