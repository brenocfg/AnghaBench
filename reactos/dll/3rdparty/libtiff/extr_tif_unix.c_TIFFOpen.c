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
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int O_BINARY ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,char const*,...) ; 
 int /*<<< orphan*/ * TIFFFdOpen (int,char const*,char const*) ; 
 int _TIFFgetMode (char const*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/ * strerror (scalar_t__) ; 

TIFF*
TIFFOpen(const char* name, const char* mode)
{
	static const char module[] = "TIFFOpen";
	int m, fd;
	TIFF* tif;

	m = _TIFFgetMode(mode, module);
	if (m == -1)
		return ((TIFF*)0);

/* for cygwin and mingw */
#ifdef O_BINARY
	m |= O_BINARY;
#endif

	fd = open(name, m, 0666);
	if (fd < 0) {
		if (errno > 0 && strerror(errno) != NULL ) {
			TIFFErrorExt(0, module, "%s: %s", name, strerror(errno) );
		} else {
			TIFFErrorExt(0, module, "%s: Cannot open", name);
		}
		return ((TIFF *)0);
	}

	tif = TIFFFdOpen((int)fd, name, mode);
	if(!tif)
		close(fd);
	return tif;
}