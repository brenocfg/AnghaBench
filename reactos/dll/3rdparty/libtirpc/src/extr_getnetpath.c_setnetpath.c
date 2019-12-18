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
struct netpath_vars {int /*<<< orphan*/ * netpath; int /*<<< orphan*/ * netpath_start; int /*<<< orphan*/ * nc_handlep; int /*<<< orphan*/ * ncp_list; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETPATH ; 
 int /*<<< orphan*/  NP_VALID ; 
 int /*<<< orphan*/  endnetconfig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct netpath_vars*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  malloc_debug (int) ; 
 int /*<<< orphan*/ * setnetconfig () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 

void *
setnetpath()
{

    struct netpath_vars *np_sessionp;   /* this session's variables */
    char *npp;				/* NETPATH env variable */

#ifdef MEM_CHK
    malloc_debug(1);
#endif

    if ((np_sessionp =
	(struct netpath_vars *)malloc(sizeof (struct netpath_vars))) == NULL) {
	return (NULL);
    }
    if ((np_sessionp->nc_handlep = setnetconfig()) == NULL) {
	//syslog (LOG_ERR, "rpc: failed to open " NETCONFIG);
	return (NULL);
    }
    np_sessionp->valid = NP_VALID;
    np_sessionp->ncp_list = NULL;
    if ((npp = getenv(NETPATH)) == NULL) {
	np_sessionp->netpath = NULL;
    } else {
	(void) endnetconfig(np_sessionp->nc_handlep);/* won't need nc session*/
	np_sessionp->nc_handlep = NULL;
	if ((np_sessionp->netpath = malloc(strlen(npp)+1)) == NULL) {
	    free(np_sessionp);
	    return (NULL);
	} else {
	    (void) strcpy(np_sessionp->netpath, npp);
	}
    }
    np_sessionp->netpath_start = np_sessionp->netpath;
    return ((void *)np_sessionp);
}