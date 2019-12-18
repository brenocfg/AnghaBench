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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {scalar_t__ nidcnt; int /*<<< orphan*/  nid_arr; } ;
typedef  TYPE_1__ nid_cb_st ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_parse_list (char const*,char,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  nid_cb ; 
 int tls1_set_groups (int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ ,scalar_t__) ; 

int tls1_set_groups_list(uint16_t **pext, size_t *pextlen, const char *str)
{
#if !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH)
    nid_cb_st ncb;
    ncb.nidcnt = 0;
    if (!CONF_parse_list(str, ':', 1, nid_cb, &ncb))
        return 0;
    if (pext == NULL)
        return 1;
    return tls1_set_groups(pext, pextlen, ncb.nid_arr, ncb.nidcnt);
#else
    return 0;
#endif
}