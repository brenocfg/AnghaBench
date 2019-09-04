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
struct errnomap_t {int nto; int other; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  errnomap ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ELIBACC ; 
 int /*<<< orphan*/  ELIBBAD ; 
 int /*<<< orphan*/  ELIBEXEC ; 
 int /*<<< orphan*/  ELIBMAX ; 
 int /*<<< orphan*/  ELIBSCN ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  NTO_EILSEQ ; 
 int /*<<< orphan*/  NTO_ELIBACC ; 
 int /*<<< orphan*/  NTO_ELIBBAD ; 
 int /*<<< orphan*/  NTO_ELIBEXEC ; 
 int /*<<< orphan*/  NTO_ELIBMAX ; 
 int /*<<< orphan*/  NTO_ELIBSCN ; 
 int /*<<< orphan*/  NTO_ENAMETOOLONG ; 
 int /*<<< orphan*/  NTO_ENOSYS ; 

int errnoconvert (int x) {
	struct errnomap_t errnomap[] = {
#if defined(__linux__)
		{NTO_ENAMETOOLONG, ENAMETOOLONG},
		{NTO_ELIBACC, ELIBACC},
		{NTO_ELIBBAD, ELIBBAD},
		{NTO_ELIBSCN, ELIBSCN},
		{NTO_ELIBMAX, ELIBMAX},
		{NTO_ELIBEXEC, ELIBEXEC},
		{NTO_EILSEQ, EILSEQ},
		{NTO_ENOSYS, ENOSYS}
#elif defined(__CYGWIN__)
		{NTO_ENAMETOOLONG, ENAMETOOLONG},
		{NTO_ENOSYS, ENOSYS}
#elif defined(__MINGW32__) || defined(MINGW32) || defined(__NetBSD__)
		/* The closest mappings from mingw's errno.h.  */
		{NTO_ENAMETOOLONG, ENAMETOOLONG},
		{NTO_ELIBACC, ESRCH},
		{NTO_ELIBBAD, ESRCH},
		{NTO_ELIBSCN, ENOEXEC},
		{NTO_ELIBMAX, EPERM},
		{NTO_ELIBEXEC, ENOEXEC},
		{NTO_EILSEQ, EILSEQ},
		{NTO_ENOSYS, ENOSYS}
#else
		{0}
#endif
	};
	int i;

	for (i = 0; i < sizeof(errnomap) / sizeof(errnomap[0]); i++)
		if (errnomap[i].nto == x)
			return errnomap[i].other;
	return x;
}