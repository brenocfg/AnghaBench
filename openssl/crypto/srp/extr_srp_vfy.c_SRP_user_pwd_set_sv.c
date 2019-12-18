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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int /*<<< orphan*/ * v; int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ SRP_user_pwd ;

/* Variables and functions */
 void* BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int MAX_LEN ; 
 int t_fromb64 (unsigned char*,int,char const*) ; 

__attribute__((used)) static int SRP_user_pwd_set_sv(SRP_user_pwd *vinfo, const char *s,
                               const char *v)
{
    unsigned char tmp[MAX_LEN];
    int len;

    vinfo->v = NULL;
    vinfo->s = NULL;

    len = t_fromb64(tmp, sizeof(tmp), v);
    if (len < 0)
        return 0;
    if (NULL == (vinfo->v = BN_bin2bn(tmp, len, NULL)))
        return 0;
    len = t_fromb64(tmp, sizeof(tmp), s);
    if (len < 0)
        goto err;
    vinfo->s = BN_bin2bn(tmp, len, NULL);
    if (vinfo->s == NULL)
        goto err;
    return 1;
 err:
    BN_free(vinfo->v);
    vinfo->v = NULL;
    return 0;
}