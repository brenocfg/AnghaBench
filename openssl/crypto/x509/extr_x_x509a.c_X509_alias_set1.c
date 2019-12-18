#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * alias; } ;
typedef  TYPE_2__ X509_CERT_AUX ;
struct TYPE_9__ {TYPE_1__* aux; } ;
typedef  TYPE_3__ X509 ;
struct TYPE_7__ {int /*<<< orphan*/ * alias; } ;

/* Variables and functions */
 int ASN1_STRING_set (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  ASN1_UTF8STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_UTF8STRING_new () ; 
 TYPE_2__* aux_get (TYPE_3__*) ; 

int X509_alias_set1(X509 *x, const unsigned char *name, int len)
{
    X509_CERT_AUX *aux;
    if (!name) {
        if (!x || !x->aux || !x->aux->alias)
            return 1;
        ASN1_UTF8STRING_free(x->aux->alias);
        x->aux->alias = NULL;
        return 1;
    }
    if ((aux = aux_get(x)) == NULL)
        return 0;
    if (aux->alias == NULL && (aux->alias = ASN1_UTF8STRING_new()) == NULL)
        return 0;
    return ASN1_STRING_set(aux->alias, name, len);
}