#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t nidcnt; int* nid_arr; } ;
typedef  TYPE_1__ nid_cb_st ;
typedef  int /*<<< orphan*/  etmp ;

/* Variables and functions */
 int EC_curve_nist2nid (char*) ; 
 size_t MAX_GROUPLIST ; 
 int NID_undef ; 
 int OBJ_ln2nid (char*) ; 
 int OBJ_sn2nid (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int nid_cb(const char *elem, int len, void *arg)
{
    nid_cb_st *narg = arg;
    size_t i;
    int nid = NID_undef;
    char etmp[20];
    if (elem == NULL)
        return 0;
    if (narg->nidcnt == MAX_GROUPLIST)
        return 0;
    if (len > (int)(sizeof(etmp) - 1))
        return 0;
    memcpy(etmp, elem, len);
    etmp[len] = 0;
# ifndef OPENSSL_NO_EC
    nid = EC_curve_nist2nid(etmp);
# endif
    if (nid == NID_undef)
        nid = OBJ_sn2nid(etmp);
    if (nid == NID_undef)
        nid = OBJ_ln2nid(etmp);
    if (nid == NID_undef)
        return 0;
    for (i = 0; i < narg->nidcnt; i++)
        if (narg->nid_arr[i] == nid)
            return 0;
    narg->nid_arr[narg->nidcnt++] = nid;
    return 1;
}