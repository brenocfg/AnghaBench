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

/* Variables and functions */
 unsigned char* strchr (unsigned char const*,char) ; 
 int tomoyo_correct_path (unsigned char const*) ; 
 int /*<<< orphan*/  tomoyo_correct_word2 (unsigned char const*,int) ; 
 int /*<<< orphan*/  tomoyo_domain_def (unsigned char const*) ; 

bool tomoyo_correct_domain(const unsigned char *domainname)
{
	if (!domainname || !tomoyo_domain_def(domainname))
		return false;
	domainname = strchr(domainname, ' ');
	if (!domainname++)
		return true;
	while (1) {
		const unsigned char *cp = strchr(domainname, ' ');

		if (!cp)
			break;
		if (*domainname != '/' ||
		    !tomoyo_correct_word2(domainname, cp - domainname))
			return false;
		domainname = cp + 1;
	}
	return tomoyo_correct_path(domainname);
}