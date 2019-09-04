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
struct zip {char* tempdir; char* zn; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  ZIP_ER_TMPOPEN ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
_zip_create_temp_output(struct zip *za, FILE **outp)
{
    char *temp;
    int tfd;
    FILE *tfp;

    if (za->tempdir) {
        if ((temp=(char *)malloc(strlen(za->tempdir)+13)) == NULL) {
            _zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
            return NULL;
        }
        sprintf(temp, "%s/.zip.XXXXXX", za->tempdir);
    }
    else {
        if ((temp=(char *)malloc(strlen(za->zn)+8)) == NULL) {
            _zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
            return NULL;
        }
        sprintf(temp, "%s.XXXXXX", za->zn);
    }

    if ((tfd=open(temp, O_RDWR|O_CREAT, 0644)) == -1) {
	_zip_error_set(&za->error, ZIP_ER_TMPOPEN, errno);
	free(temp);
	return NULL;
    }
#if 0
	umask (S_IWGRP | S_IWOTH);
    if ((tfd=mkstemp(temp)) == -1) {
	_zip_error_set(&za->error, ZIP_ER_TMPOPEN, errno);
	free(temp);
	return NULL;
    }
#endif

    if ((tfp=fdopen(tfd, "r+b")) == NULL) {
	_zip_error_set(&za->error, ZIP_ER_TMPOPEN, errno);
	close(tfd);
	(void)remove(temp);
	free(temp);
	return NULL;
    }

#if 0
#ifdef __WINDOWS__
    /*
      According to Pierre Joye, Windows in some environments per
      default creates text files, so force binary mode.
    */
    _setmode(_fileno(tfp),
#if O_BINARY
	O_BINARY
#elif _O_BINARY
	_O_BINARY
#else
	0
#endif
	);
#endif
#endif
	
    *outp = tfp;
    return temp;
}