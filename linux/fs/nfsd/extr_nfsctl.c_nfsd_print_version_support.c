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
struct nfsd_net {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_TEST ; 
 int /*<<< orphan*/  nfsd_minorversion (struct nfsd_net*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_vers (struct nfsd_net*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,char const*,char,unsigned int,int) ; 

__attribute__((used)) static ssize_t
nfsd_print_version_support(struct nfsd_net *nn, char *buf, int remaining,
		const char *sep, unsigned vers, int minor)
{
	const char *format = minor < 0 ? "%s%c%u" : "%s%c%u.%u";
	bool supported = !!nfsd_vers(nn, vers, NFSD_TEST);

	if (vers == 4 && minor >= 0 &&
	    !nfsd_minorversion(nn, minor, NFSD_TEST))
		supported = false;
	if (minor == 0 && supported)
		/*
		 * special case for backward compatability.
		 * +4.0 is never reported, it is implied by
		 * +4, unless -4.0 is present.
		 */
		return 0;
	return snprintf(buf, remaining, format, sep,
			supported ? '+' : '-', vers, minor);
}