#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; scalar_t__ length; int /*<<< orphan*/ * sn; int /*<<< orphan*/ * ln; int /*<<< orphan*/  nid; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int ASN1_OBJECT_FLAG_DYNAMIC ; 
 int ASN1_OBJECT_FLAG_DYNAMIC_DATA ; 
 int ASN1_OBJECT_FLAG_DYNAMIC_STRINGS ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_OBJECT_new () ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OBJ_F_OBJ_DUP ; 
 int /*<<< orphan*/  OBJerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OPENSSL_memdup (int /*<<< orphan*/ *,scalar_t__) ; 
 void* OPENSSL_strdup (int /*<<< orphan*/ *) ; 

ASN1_OBJECT *OBJ_dup(const ASN1_OBJECT *o)
{
    ASN1_OBJECT *r;

    if (o == NULL)
        return NULL;
    /* If object isn't dynamic it's an internal OID which is never freed */
    if (!(o->flags & ASN1_OBJECT_FLAG_DYNAMIC))
        return (ASN1_OBJECT *)o;

    r = ASN1_OBJECT_new();
    if (r == NULL) {
        OBJerr(OBJ_F_OBJ_DUP, ERR_R_ASN1_LIB);
        return NULL;
    }

    /* Set dynamic flags so everything gets freed up on error */

    r->flags = o->flags | (ASN1_OBJECT_FLAG_DYNAMIC |
                           ASN1_OBJECT_FLAG_DYNAMIC_STRINGS |
                           ASN1_OBJECT_FLAG_DYNAMIC_DATA);

    if (o->length > 0 && (r->data = OPENSSL_memdup(o->data, o->length)) == NULL)
        goto err;

    r->length = o->length;
    r->nid = o->nid;

    if (o->ln != NULL && (r->ln = OPENSSL_strdup(o->ln)) == NULL)
        goto err;

    if (o->sn != NULL && (r->sn = OPENSSL_strdup(o->sn)) == NULL)
        goto err;

    return r;
 err:
    ASN1_OBJECT_free(r);
    OBJerr(OBJ_F_OBJ_DUP, ERR_R_MALLOC_FAILURE);
    return NULL;
}