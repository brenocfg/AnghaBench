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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int BUFSIZE ; 
 scalar_t__ GetModuleFileName (int /*<<< orphan*/ *,char*,size_t) ; 
 char NUL ; 
 int /*<<< orphan*/  add_pathsep (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 scalar_t__ mch_chdir (char*) ; 
 int /*<<< orphan*/  myexit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *
my_fullpath(char *buf, char *fname, int len)
{
# ifdef WIN3264
    /* Only GetModuleFileName() will get the long file name path.
     * GetFullPathName() may still use the short (FAT) name. */
    DWORD len_read = GetModuleFileName(NULL, buf, (size_t)len);

    return (len_read > 0 && len_read < (DWORD)len) ? buf : NULL;
# else
    char	olddir[BUFSIZE];
    char	*p, *q;
    int		c;
    char	*retval = buf;

    if (strchr(fname, ':') != NULL)	/* already expanded */
    {
	strncpy(buf, fname, len);
    }
    else
    {
	*buf = NUL;
	/*
	 * change to the directory for a moment,
	 * and then do the getwd() (and get back to where we were).
	 * This will get the correct path name with "../" things.
	 */
	p = strrchr(fname, '/');
	q = strrchr(fname, '\\');
	if (q != NULL && (p == NULL || q > p))
	    p = q;
	q = strrchr(fname, ':');
	if (q != NULL && (p == NULL || q > p))
	    p = q;
	if (p != NULL)
	{
	    if (getcwd(olddir, BUFSIZE) == NULL)
	    {
		p = NULL;		/* can't get current dir: don't chdir */
		retval = NULL;
	    }
	    else
	    {
		if (p == fname)		/* /fname		*/
		    q = p + 1;		/* -> /			*/
		else if (q + 1 == p)	/* ... c:\foo		*/
		    q = p + 1;		/* -> c:\		*/
		else			/* but c:\foo\bar	*/
		    q = p;		/* -> c:\foo		*/

		c = *q;			/* truncate at start of fname */
		*q = NUL;
		if (mch_chdir(fname))	/* change to the directory */
		    retval = NULL;
		else
		{
		    fname = q;
		    if (c == '\\')	/* if we cut the name at a */
			fname++;	/* '\', don't add it again */
		}
		*q = c;
	    }
	}
	if (getcwd(buf, len) == NULL)
	{
	    retval = NULL;
	    *buf = NUL;
	}
	/*
	 * Concatenate the file name to the path.
	 */
	if (strlen(buf) + strlen(fname) >= len - 1)
	{
	    printf("ERROR: File name too long!\n");
	    myexit(1);
	}
	add_pathsep(buf);
	strcat(buf, fname);
	if (p)
	    mch_chdir(olddir);
    }

    /* Replace forward slashes with backslashes, required for the path to a
     * command. */
    while ((p = strchr(buf, '/')) != NULL)
	*p = '\\';

    return retval;
# endif
}