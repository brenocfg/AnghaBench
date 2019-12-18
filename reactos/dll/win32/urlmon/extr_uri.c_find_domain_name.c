#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  tld_name; } ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  StrCmpNIW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * memrchrW (int /*<<< orphan*/  const*,char,int) ; 
 TYPE_1__* recognized_tlds ; 

void find_domain_name(const WCHAR *host, DWORD host_len,
                             INT *domain_start) {
    const WCHAR *last_tld, *sec_last_tld, *end;

    end = host+host_len-1;

    *domain_start = -1;

    /* There has to be at least enough room for a '.' followed by a
     * 3-character TLD for a domain to even exist in the host name.
     */
    if(host_len < 4)
        return;

    last_tld = memrchrW(host, '.', host_len);
    if(!last_tld)
        /* http://hostname -> has no domain name. */
        return;

    sec_last_tld = memrchrW(host, '.', last_tld-host);
    if(!sec_last_tld) {
        /* If the '.' is at the beginning of the host there
         * has to be at least 3 characters in the TLD for it
         * to be valid.
         *  Ex: .com -> .com as the domain name.
         *      .co  -> has no domain name.
         */
        if(last_tld-host == 0) {
            if(end-(last_tld-1) < 3)
                return;
        } else if(last_tld-host == 3) {
            DWORD i;

            /* If there are three characters in front of last_tld and
             * they are on the list of recognized TLDs, then this
             * host doesn't have a domain (since the host only contains
             * a TLD name.
             *  Ex: edu.uk -> has no domain name.
             *      foo.uk -> foo.uk as the domain name.
             */
            for(i = 0; i < ARRAY_SIZE(recognized_tlds); ++i) {
                if(!StrCmpNIW(host, recognized_tlds[i].tld_name, 3))
                    return;
            }
        } else if(last_tld-host < 3)
            /* Anything less than 3 characters is considered part
             * of the TLD name.
             *  Ex: ak.uk -> Has no domain name.
             */
            return;

        /* Otherwise the domain name is the whole host name. */
        *domain_start = 0;
    } else if(end+1-last_tld > 3) {
        /* If the last_tld has more than 3 characters, then it's automatically
         * considered the TLD of the domain name.
         *  Ex: www.winehq.org.uk.test -> uk.test as the domain name.
         */
        *domain_start = (sec_last_tld+1)-host;
    } else if(last_tld - (sec_last_tld+1) < 4) {
        DWORD i;
        /* If the sec_last_tld is 3 characters long it HAS to be on the list of
         * recognized to still be considered part of the TLD name, otherwise
         * it's considered the domain name.
         *  Ex: www.google.com.uk -> google.com.uk as the domain name.
         *      www.google.foo.uk -> foo.uk as the domain name.
         */
        if(last_tld - (sec_last_tld+1) == 3) {
            for(i = 0; i < ARRAY_SIZE(recognized_tlds); ++i) {
                if(!StrCmpNIW(sec_last_tld+1, recognized_tlds[i].tld_name, 3)) {
                    const WCHAR *domain = memrchrW(host, '.', sec_last_tld-host);

                    if(!domain)
                        *domain_start = 0;
                    else
                        *domain_start = (domain+1) - host;
                    TRACE("Found domain name %s\n", debugstr_wn(host+*domain_start,
                                                        (host+host_len)-(host+*domain_start)));
                    return;
                }
            }

            *domain_start = (sec_last_tld+1)-host;
        } else {
            /* Since the sec_last_tld is less than 3 characters it's considered
             * part of the TLD.
             *  Ex: www.google.fo.uk -> google.fo.uk as the domain name.
             */
            const WCHAR *domain = memrchrW(host, '.', sec_last_tld-host);

            if(!domain)
                *domain_start = 0;
            else
                *domain_start = (domain+1) - host;
        }
    } else {
        /* The second to last TLD has more than 3 characters making it
         * the domain name.
         *  Ex: www.google.test.us -> test.us as the domain name.
         */
        *domain_start = (sec_last_tld+1)-host;
    }

    TRACE("Found domain name %s\n", debugstr_wn(host+*domain_start,
                                        (host+host_len)-(host+*domain_start)));
}