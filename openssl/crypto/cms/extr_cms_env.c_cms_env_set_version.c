#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int version; scalar_t__ unprotectedAttrs; scalar_t__ originatorInfo; int /*<<< orphan*/  recipientInfos; } ;
struct TYPE_9__ {TYPE_1__* ktri; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_8__ {scalar_t__ version; } ;
typedef  TYPE_3__ CMS_RecipientInfo ;
typedef  TYPE_4__ CMS_EnvelopedData ;

/* Variables and functions */
 scalar_t__ CMS_RECIPINFO_OTHER ; 
 scalar_t__ CMS_RECIPINFO_PASS ; 
 scalar_t__ CMS_RECIPINFO_TRANS ; 
 int /*<<< orphan*/  cms_env_set_originfo_version (TYPE_4__*) ; 
 int sk_CMS_RecipientInfo_num (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_CMS_RecipientInfo_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cms_env_set_version(CMS_EnvelopedData *env)
{
    int i;
    CMS_RecipientInfo *ri;

    /*
     * Can't set version higher than 4 so if 4 or more already nothing to do.
     */
    if (env->version >= 4)
        return;

    cms_env_set_originfo_version(env);

    if (env->version >= 3)
        return;

    for (i = 0; i < sk_CMS_RecipientInfo_num(env->recipientInfos); i++) {
        ri = sk_CMS_RecipientInfo_value(env->recipientInfos, i);
        if (ri->type == CMS_RECIPINFO_PASS || ri->type == CMS_RECIPINFO_OTHER) {
            env->version = 3;
            return;
        } else if (ri->type != CMS_RECIPINFO_TRANS
                   || ri->d.ktri->version != 0) {
            env->version = 2;
        }
    }
    if (env->originatorInfo || env->unprotectedAttrs)
        env->version = 2;
    if (env->version == 2)
        return;
    env->version = 0;
}