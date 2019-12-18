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
struct nsinfo {int dummy; } ;
struct nscookie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nsinfo__mountns_enter (struct nsinfo*,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 char* realpath (char const*,int /*<<< orphan*/ *) ; 

char *nsinfo__realpath(const char *path, struct nsinfo *nsi)
{
	char *rpath;
	struct nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	rpath = realpath(path, NULL);
	nsinfo__mountns_exit(&nsc);

	return rpath;
}