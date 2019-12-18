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
struct stat {scalar_t__ st_size; } ;
struct nsinfo {int dummy; } ;
struct nscookie {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int copyfile_offset (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fchmod (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int link (char*,char const*) ; 
 char* memmove (char*,char*,scalar_t__) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (struct nsinfo*,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int slow_copyfile (char const*,char*,struct nsinfo*) ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int copyfile_mode_ns(const char *from, const char *to, mode_t mode,
			    struct nsinfo *nsi)
{
	int fromfd, tofd;
	struct stat st;
	int err;
	char *tmp = NULL, *ptr = NULL;
	struct nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	err = stat(from, &st);
	nsinfo__mountns_exit(&nsc);
	if (err)
		goto out;
	err = -1;

	/* extra 'x' at the end is to reserve space for '.' */
	if (asprintf(&tmp, "%s.XXXXXXx", to) < 0) {
		tmp = NULL;
		goto out;
	}
	ptr = strrchr(tmp, '/');
	if (!ptr)
		goto out;
	ptr = memmove(ptr + 1, ptr, strlen(ptr) - 1);
	*ptr = '.';

	tofd = mkstemp(tmp);
	if (tofd < 0)
		goto out;

	if (st.st_size == 0) { /* /proc? do it slowly... */
		err = slow_copyfile(from, tmp, nsi);
		if (!err && fchmod(tofd, mode))
			err = -1;
		goto out_close_to;
	}

	if (fchmod(tofd, mode))
		goto out_close_to;

	nsinfo__mountns_enter(nsi, &nsc);
	fromfd = open(from, O_RDONLY);
	nsinfo__mountns_exit(&nsc);
	if (fromfd < 0)
		goto out_close_to;

	err = copyfile_offset(fromfd, 0, tofd, 0, st.st_size);

	close(fromfd);
out_close_to:
	close(tofd);
	if (!err)
		err = link(tmp, to);
	unlink(tmp);
out:
	free(tmp);
	return err;
}