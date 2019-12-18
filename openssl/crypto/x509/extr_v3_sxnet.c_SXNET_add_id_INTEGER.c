#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ids; int /*<<< orphan*/  version; } ;
struct TYPE_10__ {int /*<<< orphan*/ * zone; int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ SXNETID ;
typedef  TYPE_2__ SXNET ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  SXNETID_free (TYPE_1__*) ; 
 TYPE_1__* SXNETID_new () ; 
 int /*<<< orphan*/  SXNET_free (TYPE_2__*) ; 
 scalar_t__ SXNET_get_id_INTEGER (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* SXNET_new () ; 
 int /*<<< orphan*/  X509V3_F_SXNET_ADD_ID_INTEGER ; 
 int /*<<< orphan*/  X509V3_R_DUPLICATE_ZONE_ID ; 
 int /*<<< orphan*/  X509V3_R_INVALID_NULL_ARGUMENT ; 
 int /*<<< orphan*/  X509V3_R_USER_TOO_LONG ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_SXNETID_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int strlen (char const*) ; 

int SXNET_add_id_INTEGER(SXNET **psx, ASN1_INTEGER *zone, const char *user,
                         int userlen)
{
    SXNET *sx = NULL;
    SXNETID *id = NULL;

    if (psx == NULL || zone == NULL || user == NULL) {
        X509V3err(X509V3_F_SXNET_ADD_ID_INTEGER,
                  X509V3_R_INVALID_NULL_ARGUMENT);
        return 0;
    }
    if (userlen == -1)
        userlen = strlen(user);
    if (userlen > 64) {
        X509V3err(X509V3_F_SXNET_ADD_ID_INTEGER, X509V3_R_USER_TOO_LONG);
        return 0;
    }
    if (*psx == NULL) {
        if ((sx = SXNET_new()) == NULL)
            goto err;
        if (!ASN1_INTEGER_set(sx->version, 0))
            goto err;
        *psx = sx;
    } else
        sx = *psx;
    if (SXNET_get_id_INTEGER(sx, zone)) {
        X509V3err(X509V3_F_SXNET_ADD_ID_INTEGER, X509V3_R_DUPLICATE_ZONE_ID);
        return 0;
    }

    if ((id = SXNETID_new()) == NULL)
        goto err;
    if (userlen == -1)
        userlen = strlen(user);

    if (!ASN1_OCTET_STRING_set(id->user, (const unsigned char *)user, userlen))
        goto err;
    if (!sk_SXNETID_push(sx->ids, id))
        goto err;
    id->zone = zone;
    return 1;

 err:
    X509V3err(X509V3_F_SXNET_ADD_ID_INTEGER, ERR_R_MALLOC_FAILURE);
    SXNETID_free(id);
    SXNET_free(sx);
    *psx = NULL;
    return 0;
}