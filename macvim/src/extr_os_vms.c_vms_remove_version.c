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
typedef  char char_u ;

/* Variables and functions */
 char* vim_strchr (void*,char) ; 
 char* vim_strrchr (void*,char) ; 

void
vms_remove_version(void * fname)
{
    char_u	*cp;
    char_u	*fp;

    if ((cp = vim_strchr( fname, ';')) != NULL) /* remove version */
	*cp = '\0';
    else if ((cp = vim_strrchr( fname, '.')) != NULL )
    {
	if      ((fp = vim_strrchr( fname, ']')) != NULL ) {;}
	else if ((fp = vim_strrchr( fname, '>')) != NULL ) {;}
	else fp = fname;

	while ( *fp != '\0' && fp < cp )
	    if ( *fp++ == '.' )
		*cp = '\0';
    }
    return ;
}