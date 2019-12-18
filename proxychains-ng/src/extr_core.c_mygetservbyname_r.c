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
struct servent {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MUTEX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MUTEX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int /*<<< orphan*/  PFUNC () ; 
 struct servent* getservbyname (char const*,char const*) ; 
 int getservbyname_r (char const*,char const*,struct servent*,char*,size_t,struct servent**) ; 
 int /*<<< orphan*/  servbyname_lock ; 

__attribute__((used)) static int mygetservbyname_r(const char* name, const char* proto, struct servent* result_buf,
			   char* buf, size_t buflen, struct servent** result) {
	PFUNC();
#ifdef HAVE_GNU_GETSERVBYNAME_R
	PDEBUG("using host getservbyname_r\n");
	return getservbyname_r(name, proto, result_buf, buf, buflen, result);
#endif
	struct servent *res;
	int ret;
	(void) buf; (void) buflen;
	MUTEX_LOCK(&servbyname_lock);
	res = getservbyname(name, proto);
	if(res) {
		*result_buf = *res;
		*result = result_buf;
		ret = 0;
	} else {
		*result = NULL;
		ret = ENOENT;
	}
	MUTEX_UNLOCK(&servbyname_lock);
	return ret;
}