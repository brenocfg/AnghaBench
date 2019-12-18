#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int sec_level; } ;
struct TYPE_5__ {char* name; int algorithm_mkey; int algorithm_auth; int algorithm_enc; int algorithm_mac; int algo_strength; int id; int min_tls; scalar_t__ valid; } ;
typedef  TYPE_1__ SSL_CIPHER ;
typedef  int /*<<< orphan*/  CIPHER_ORDER ;
typedef  TYPE_2__ CERT ;

/* Variables and functions */
 int CIPHER_ADD ; 
 int CIPHER_DEL ; 
 int CIPHER_KILL ; 
 int CIPHER_ORD ; 
 int CIPHER_SPECIAL ; 
 scalar_t__ ITEM_SEP (char const) ; 
 int SSL_DEFAULT_MASK ; 
 int /*<<< orphan*/  SSL_F_SSL_CIPHER_PROCESS_RULESTR ; 
 int /*<<< orphan*/  SSL_R_INVALID_COMMAND ; 
 int SSL_STRONG_MASK ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isalnum (unsigned char) ; 
 int /*<<< orphan*/  ssl_cipher_apply_rule (int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int ssl_cipher_strength_sort (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int ssl_cipher_process_rulestr(const char *rule_str,
                                      CIPHER_ORDER **head_p,
                                      CIPHER_ORDER **tail_p,
                                      const SSL_CIPHER **ca_list, CERT *c)
{
    uint32_t alg_mkey, alg_auth, alg_enc, alg_mac, algo_strength;
    int min_tls;
    const char *l, *buf;
    int j, multi, found, rule, retval, ok, buflen;
    uint32_t cipher_id = 0;
    char ch;

    retval = 1;
    l = rule_str;
    for ( ; ; ) {
        ch = *l;

        if (ch == '\0')
            break;              /* done */
        if (ch == '-') {
            rule = CIPHER_DEL;
            l++;
        } else if (ch == '+') {
            rule = CIPHER_ORD;
            l++;
        } else if (ch == '!') {
            rule = CIPHER_KILL;
            l++;
        } else if (ch == '@') {
            rule = CIPHER_SPECIAL;
            l++;
        } else {
            rule = CIPHER_ADD;
        }

        if (ITEM_SEP(ch)) {
            l++;
            continue;
        }

        alg_mkey = 0;
        alg_auth = 0;
        alg_enc = 0;
        alg_mac = 0;
        min_tls = 0;
        algo_strength = 0;

        for (;;) {
            ch = *l;
            buf = l;
            buflen = 0;
#ifndef CHARSET_EBCDIC
            while (((ch >= 'A') && (ch <= 'Z')) ||
                   ((ch >= '0') && (ch <= '9')) ||
                   ((ch >= 'a') && (ch <= 'z')) ||
                   (ch == '-') || (ch == '.') || (ch == '='))
#else
            while (isalnum((unsigned char)ch) || (ch == '-') || (ch == '.')
                   || (ch == '='))
#endif
            {
                ch = *(++l);
                buflen++;
            }

            if (buflen == 0) {
                /*
                 * We hit something we cannot deal with,
                 * it is no command or separator nor
                 * alphanumeric, so we call this an error.
                 */
                SSLerr(SSL_F_SSL_CIPHER_PROCESS_RULESTR, SSL_R_INVALID_COMMAND);
                retval = found = 0;
                l++;
                break;
            }

            if (rule == CIPHER_SPECIAL) {
                found = 0;      /* unused -- avoid compiler warning */
                break;          /* special treatment */
            }

            /* check for multi-part specification */
            if (ch == '+') {
                multi = 1;
                l++;
            } else {
                multi = 0;
            }

            /*
             * Now search for the cipher alias in the ca_list. Be careful
             * with the strncmp, because the "buflen" limitation
             * will make the rule "ADH:SOME" and the cipher
             * "ADH-MY-CIPHER" look like a match for buflen=3.
             * So additionally check whether the cipher name found
             * has the correct length. We can save a strlen() call:
             * just checking for the '\0' at the right place is
             * sufficient, we have to strncmp() anyway. (We cannot
             * use strcmp(), because buf is not '\0' terminated.)
             */
            j = found = 0;
            cipher_id = 0;
            while (ca_list[j]) {
                if (strncmp(buf, ca_list[j]->name, buflen) == 0
                    && (ca_list[j]->name[buflen] == '\0')) {
                    found = 1;
                    break;
                } else
                    j++;
            }

            if (!found)
                break;          /* ignore this entry */

            if (ca_list[j]->algorithm_mkey) {
                if (alg_mkey) {
                    alg_mkey &= ca_list[j]->algorithm_mkey;
                    if (!alg_mkey) {
                        found = 0;
                        break;
                    }
                } else {
                    alg_mkey = ca_list[j]->algorithm_mkey;
                }
            }

            if (ca_list[j]->algorithm_auth) {
                if (alg_auth) {
                    alg_auth &= ca_list[j]->algorithm_auth;
                    if (!alg_auth) {
                        found = 0;
                        break;
                    }
                } else {
                    alg_auth = ca_list[j]->algorithm_auth;
                }
            }

            if (ca_list[j]->algorithm_enc) {
                if (alg_enc) {
                    alg_enc &= ca_list[j]->algorithm_enc;
                    if (!alg_enc) {
                        found = 0;
                        break;
                    }
                } else {
                    alg_enc = ca_list[j]->algorithm_enc;
                }
            }

            if (ca_list[j]->algorithm_mac) {
                if (alg_mac) {
                    alg_mac &= ca_list[j]->algorithm_mac;
                    if (!alg_mac) {
                        found = 0;
                        break;
                    }
                } else {
                    alg_mac = ca_list[j]->algorithm_mac;
                }
            }

            if (ca_list[j]->algo_strength & SSL_STRONG_MASK) {
                if (algo_strength & SSL_STRONG_MASK) {
                    algo_strength &=
                        (ca_list[j]->algo_strength & SSL_STRONG_MASK) |
                        ~SSL_STRONG_MASK;
                    if (!(algo_strength & SSL_STRONG_MASK)) {
                        found = 0;
                        break;
                    }
                } else {
                    algo_strength = ca_list[j]->algo_strength & SSL_STRONG_MASK;
                }
            }

            if (ca_list[j]->algo_strength & SSL_DEFAULT_MASK) {
                if (algo_strength & SSL_DEFAULT_MASK) {
                    algo_strength &=
                        (ca_list[j]->algo_strength & SSL_DEFAULT_MASK) |
                        ~SSL_DEFAULT_MASK;
                    if (!(algo_strength & SSL_DEFAULT_MASK)) {
                        found = 0;
                        break;
                    }
                } else {
                    algo_strength |=
                        ca_list[j]->algo_strength & SSL_DEFAULT_MASK;
                }
            }

            if (ca_list[j]->valid) {
                /*
                 * explicit ciphersuite found; its protocol version does not
                 * become part of the search pattern!
                 */

                cipher_id = ca_list[j]->id;
            } else {
                /*
                 * not an explicit ciphersuite; only in this case, the
                 * protocol version is considered part of the search pattern
                 */

                if (ca_list[j]->min_tls) {
                    if (min_tls != 0 && min_tls != ca_list[j]->min_tls) {
                        found = 0;
                        break;
                    } else {
                        min_tls = ca_list[j]->min_tls;
                    }
                }
            }

            if (!multi)
                break;
        }

        /*
         * Ok, we have the rule, now apply it
         */
        if (rule == CIPHER_SPECIAL) { /* special command */
            ok = 0;
            if ((buflen == 8) && strncmp(buf, "STRENGTH", 8) == 0) {
                ok = ssl_cipher_strength_sort(head_p, tail_p);
            } else if (buflen == 10 && strncmp(buf, "SECLEVEL=", 9) == 0) {
                int level = buf[9] - '0';
                if (level < 0 || level > 5) {
                    SSLerr(SSL_F_SSL_CIPHER_PROCESS_RULESTR,
                           SSL_R_INVALID_COMMAND);
                } else {
                    c->sec_level = level;
                    ok = 1;
                }
            } else {
                SSLerr(SSL_F_SSL_CIPHER_PROCESS_RULESTR, SSL_R_INVALID_COMMAND);
            }
            if (ok == 0)
                retval = 0;
            /*
             * We do not support any "multi" options
             * together with "@", so throw away the
             * rest of the command, if any left, until
             * end or ':' is found.
             */
            while ((*l != '\0') && !ITEM_SEP(*l))
                l++;
        } else if (found) {
            ssl_cipher_apply_rule(cipher_id,
                                  alg_mkey, alg_auth, alg_enc, alg_mac,
                                  min_tls, algo_strength, rule, -1, head_p,
                                  tail_p);
        } else {
            while ((*l != '\0') && !ITEM_SEP(*l))
                l++;
        }
        if (*l == '\0')
            break;              /* done */
    }

    return retval;
}