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
struct nsinfo {int need_setns; int nstgid; int tgid; } ;
struct nscookie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 struct nsinfo* nsinfo__copy (struct nsinfo*) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (struct nsinfo*,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__put (struct nsinfo*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int dso__find_perf_map(char *filebuf, size_t bufsz,
			      struct nsinfo **nsip)
{
	struct nscookie nsc;
	struct nsinfo *nsi;
	struct nsinfo *nnsi;
	int rc = -1;

	nsi = *nsip;

	if (nsi->need_setns) {
		snprintf(filebuf, bufsz, "/tmp/perf-%d.map", nsi->nstgid);
		nsinfo__mountns_enter(nsi, &nsc);
		rc = access(filebuf, R_OK);
		nsinfo__mountns_exit(&nsc);
		if (rc == 0)
			return rc;
	}

	nnsi = nsinfo__copy(nsi);
	if (nnsi) {
		nsinfo__put(nsi);

		nnsi->need_setns = false;
		snprintf(filebuf, bufsz, "/tmp/perf-%d.map", nnsi->tgid);
		*nsip = nnsi;
		rc = 0;
	}

	return rc;
}